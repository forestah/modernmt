/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class eu_modernmt_vocabulary_Vocabulary */

#ifndef _Included_eu_modernmt_vocabulary_Vocabulary
#define _Included_eu_modernmt_vocabulary_Vocabulary
#ifdef __cplusplus
extern "C" {
#endif
#undef eu_modernmt_vocabulary_Vocabulary_VOCABULARY_UNKNOWN_WORD
#define eu_modernmt_vocabulary_Vocabulary_VOCABULARY_UNKNOWN_WORD 0L
#undef eu_modernmt_vocabulary_Vocabulary_VOCABULARY_WORD_ID_START
#define eu_modernmt_vocabulary_Vocabulary_VOCABULARY_WORD_ID_START 1000L
/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    instantiate
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_modernmt_vocabulary_Vocabulary_instantiate
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    getId
 * Signature: (Ljava/lang/String;Z)I
 */
JNIEXPORT jint JNICALL Java_eu_modernmt_vocabulary_Vocabulary_getId
  (JNIEnv *, jobject, jstring, jboolean);

/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    encodeLine
 * Signature: ([Ljava/lang/String;Z)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_modernmt_vocabulary_Vocabulary_encodeLine
  (JNIEnv *, jobject, jobjectArray, jboolean);

/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    encodeLines
 * Signature: ([[Ljava/lang/String;[[IZ)V
 */
JNIEXPORT void JNICALL Java_eu_modernmt_vocabulary_Vocabulary_encodeLines
  (JNIEnv *, jobject, jobjectArray, jobjectArray, jboolean);

/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    getWord
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_modernmt_vocabulary_Vocabulary_getWord
  (JNIEnv *, jobject, jint);

/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    decodeLine
 * Signature: ([I)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_eu_modernmt_vocabulary_Vocabulary_decodeLine
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    decodeLines
 * Signature: ([[I[[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_modernmt_vocabulary_Vocabulary_decodeLines
  (JNIEnv *, jobject, jobjectArray, jobjectArray);

/*
 * Class:     eu_modernmt_vocabulary_Vocabulary
 * Method:    dispose
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_eu_modernmt_vocabulary_Vocabulary_dispose
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
