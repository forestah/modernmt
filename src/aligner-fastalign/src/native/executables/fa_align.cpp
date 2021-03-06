//
// Created by Davide Caroselli on 04/09/16.
//

#include <iostream>
#include <fstream>
#include <fastalign/Corpus.h>
#include <fastalign/FastAligner.h>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <thread>

#ifdef _OPENMP
#include <thread>
#include <omp.h>
#endif

using namespace std;
using namespace mmt;
using namespace mmt::fastalign;


namespace {
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t GENERIC_ERROR = 2;
    const size_t SUCCESS = 0;

    struct args_t {
        string output_path;
        string model_path;
        string input_path;
        string source_lang;
        string target_lang;
        bool print_alignments = true;
        bool print_scores = true;

        Symmetrization strategy = GrowDiagonalFinalAnd;
        size_t buffer_size = 100000;
    };
} // namespace

namespace po = boost::program_options;
namespace fs = boost::filesystem;


bool ParseArgs(int argc, const char *argv[], args_t *args) {
    po::options_description desc("Runs FastAlign model on a collection of parallel files "
                                 "and outputs alignments and scores in the output folder");
    desc.add_options()
            ("help,h", "print this help message")
            ("model,m", po::value<string>()->required(), "the FastAlign model path")
            ("output,o", po::value<string>()->required(), "output folder for \"*.score\" and \"*.align\" files")
            ("source,s", po::value<string>()->required(), "source language")
            ("target,t", po::value<string>()->required(), "target language")
            ("input,i", po::value<string>()->required(), "input folder containing the parallel files collection")
            ("strategy,a", po::value<size_t>(),
             "symmetrization strategy, valid values are (1) GrowDiagonalFinalAnd, (2) GrowDiagonal, (3) Intersection "
             "(4) Union. Default strategy is \"GrowDiagonalFinalAnd\"")
            ("batch-size,b", po::value<size_t>(), "input batch size, expressed in number of lines")
            ("skip-alignments", "skip the creation of \"*.align\" files")
            ("skip-scores", "skip the creation of \"*.score\" files");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return false;
        }

        po::notify(vm);

        args->model_path = vm["model"].as<string>();
        args->input_path = vm["input"].as<string>();
        args->output_path = vm["output"].as<string>();
        args->source_lang = vm["source"].as<string>();
        args->target_lang = vm["target"].as<string>();

        args->print_alignments = !vm.count("skip-alignments");
        args->print_scores = !vm.count("skip-scores");

        if (vm.count("strategy"))
            args->strategy = (Symmetrization) vm["strategy"].as<size_t>();

        if (vm.count("batch-size"))
            args->buffer_size = vm["batch-size"].as<size_t>();
    } catch (po::error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        return false;
    }

    return true;
}


void PrintAlignment(vector<alignment_t> &alignments, ofstream &out) {
    for (auto a = alignments.begin(); a != alignments.end(); ++a) {
        for (size_t i = 0; i < a->points.size(); ++i) {
            if (i > 0)
                out << ' ';
            out << a->points[i].first << '-' << a->points[i].second;
        }

        out << endl;
    }
}

void PrintScore(vector<alignment_t> &alignments, ofstream &out) {
    for (auto a = alignments.begin(); a != alignments.end(); ++a) {
        out << a->score << endl;
    }
}

void AlignCorpus(const Corpus &corpus, size_t buffer_size, Symmetrization strategy, FastAligner &aligner,
                 const string &outputPath, bool printAlignments, bool printScores) {
    CorpusReader reader(corpus, &aligner.GetVocabulary());

    vector<pair<wordvec_t, wordvec_t>> batch;
    vector<alignment_t> alignments;

    string alignPath = (fs::path(outputPath) / (corpus.GetName() + ".align")).string();
    string scorePath = (fs::path(outputPath) / (corpus.GetName() + ".score")).string();

    ofstream alignStream;
    if (printAlignments)
        alignStream.open(alignPath.c_str(), ios_base::out);

    ofstream scoreStream;
    if (printScores)
        scoreStream.open(scorePath.c_str(), ios_base::out);

    while (reader.Read(batch, buffer_size)) {
        aligner.GetAlignments(batch, alignments, strategy);

        if (printAlignments)
            PrintAlignment(alignments, alignStream);
        if (printScores)
            PrintScore(alignments, scoreStream);

        alignments.clear();
        batch.clear();
    }
}

int main(int argc, const char *argv[]) {
    int threads = 1;

#ifdef _OPENMP
    threads = thread::hardware_concurrency();

    omp_set_dynamic(0);
    omp_set_num_threads(threads);
#endif

    args_t args;

    if (!ParseArgs(argc, argv, &args))
        return ERROR_IN_COMMAND_LINE;

    if (!fs::exists(args.input_path) || !fs::is_directory(args.input_path)) {
        cerr << "ERROR: input path is not a valid directory" << endl;
        return GENERIC_ERROR;
    }

    if (!fs::is_regular(args.model_path)) {
        cerr << "ERROR: model path is not a valid directory" << endl;
        return GENERIC_ERROR;
    }

    if (!fs::is_directory(args.output_path))
        fs::create_directories(args.output_path);

    vector<Corpus> corpora;
    Corpus::List(args.input_path, args.source_lang, args.target_lang, corpora);

    if (corpora.empty())
        exit(0);

    FastAligner aligner(args.model_path, threads);

    // perform alignment of all corpora sequentially; multi-threading is used for each corpus
    for (size_t i = 0; i < corpora.size(); ++i) {
        Corpus &corpus = corpora[i];
        AlignCorpus(corpus, args.buffer_size, args.strategy, aligner, args.output_path,
                    args.print_alignments, args.print_scores);
    }

    return SUCCESS;
}