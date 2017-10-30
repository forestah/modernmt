//
// Created by Davide  Caroselli on 08/05/17.
//

#ifndef MMT_FASTALIGN_BIDIRECTIONALMODEL_H
#define MMT_FASTALIGN_BIDIRECTIONALMODEL_H

using namespace std;

#include <memory>
#include <vector>
#include <string>

#include "Model.h"
#include "Vocabulary.h"

namespace mmt {
    namespace fastalign {

        typedef std::vector<std::unordered_map<word_t, std::pair<float, float>>> bitable_t;

        class BidirectionalModel : public Model {
        public:
            BidirectionalModel(std::shared_ptr<bitable_t> table, bool forward, bool use_null,
                               bool favor_diagonal, double prob_align_null, double diagonal_tension);

            float GetProbability(word_t source, word_t target) override;

            inline void IncrementProbability(word_t source, word_t target, double amount) override {
                // no-op
            }

            void ExportLexicalModel(const string &filename, const Vocabulary *vb);

            static void Store(const BidirectionalModel *forward, const BidirectionalModel *backward,
                              const string &filename);

            static void Open(const string &filename, Model **outForward, Model **outBackward);

        private:
            const std::shared_ptr<bitable_t> table;
        };
    }
}


#endif //MMT_FASTALIGN_BIDIRECTIONALMODEL_H
