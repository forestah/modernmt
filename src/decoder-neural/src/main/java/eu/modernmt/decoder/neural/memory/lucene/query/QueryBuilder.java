package eu.modernmt.decoder.neural.memory.lucene.query;

import eu.modernmt.lang.LanguagePair;
import eu.modernmt.model.ContextVector;
import eu.modernmt.model.Sentence;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.search.Query;

import java.util.UUID;

/**
 * Created by davide on 24/05/17.
 */
public interface QueryBuilder {

    boolean isLongQuery(int queryLength);

    Query getByHash(long memory, String hash);

    Query bestMatchingSuggestion(Analyzer analyzer, UUID user, LanguagePair direction, Sentence sentence, ContextVector context);

}
