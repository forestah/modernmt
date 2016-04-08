package eu.modernmt.processing.tokenizer;

import eu.modernmt.model.xmessage.XFormat;
import eu.modernmt.processing.framework.string.InvalidOperationException;
import eu.modernmt.processing.framework.string.XMLEditableString;

import java.util.regex.Matcher;

/**
 * Created by davide on 08/04/16.
 */
public class XMessageTokenizer implements Tokenizer {

    @Override
    public XMLEditableString call(XMLEditableString string) throws InvalidOperationException {
        XMLEditableString.Editor editor = string.getEditor();

        Matcher m = XFormat.PLACEHOLDER_PATTERN.matcher(string.toString());

        while (m.find()) {
            int start = m.start();
            int end = m.end();

            editor.setWord(start, end - start);
        }

        return editor.commitChanges();
    }

    @Override
    public void close() {
        // Nothing to do
    }

}