#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

void exit_with_error(const char *err_msg)   // prints error message
{
    fprintf(stderr, "%s\n", err_msg);
    exit(-1);
}

int word_count(char *para, char *lengths, char *spbr_lengths, int max_line_length)  // counts the word length in paragraph
{
    char *location;
    char *prev = para;
    char last_cnt = 0;
    int word_cnt = 0;


    // counts the number of words in paragraph
    while (location = strchr((prev), ' ')){ // loc = for 1st occurrence of para point to ' '
        if ((char) (location - prev) < (int) max_line_length)
            lengths[word_cnt] = (char) (location - prev);
        else
            exit_with_error("Cannot Justify: Insufficient lineLength.");
        prev = location;
        while (*prev == ' '){
            prev++;
            spbr_lengths[word_cnt]++; // add whitespace counter
        }
        word_cnt++;
    }

    // handle last word
    while (*prev != '\0') { // while word is
        prev++;
        last_cnt++;
    }
    if (last_cnt)
        lengths[word_cnt] = last_cnt;

    return word_cnt;
}

void write_to_buf_one_word(
        char *buf,
        int line_len,
        char *word_pointer,
        char word_len
)
{
    int i;

    // like always, we'll assume that word_len <= line_len
    for (i=0; i<word_len; i++)
        buf[i] = word_pointer[i];
    // fill in the remaining bytes with ' '
    memset((buf+i), ' ', line_len - word_len);
}

void write_to_buf(
        char *buf,
        int line_len,
        int char_cnt,
        char *para,
        char *para_pointer,
        int start_word_idx,
        int end_word_idx,
        char *word_lens,
        char *spbr_lens)
{
    int total_words = end_word_idx - start_word_idx;
    if (total_words == 1) {
        // special case, shortcut return
        write_to_buf_one_word(buf, line_len, para_pointer, word_lens[start_word_idx]);
        return;
    }

    int whsp_needed = line_len - char_cnt;
    int whsp_for_each_word = whsp_needed / (total_words-1);
    int extra_whsp = whsp_needed % (total_words-1); // tells how many holes will use extra whsp
    int curr_word_idx = start_word_idx;

    char word_turn = 1; // goes between word's turn and space turn, word=1, space=0
    int buf_pointer = 0;

    int i=0;
    int j;

    // while (buf[i] != '\0'){
    while (i < line_len){
        if (word_turn) {
            for (j=0; j<word_lens[curr_word_idx]; j++){
                buf[i] = *(para_pointer + j);
                i++;
            }
            // update para_pointer
            para_pointer += (word_lens[curr_word_idx] + spbr_lens[curr_word_idx]);
            // update curr_word_idx
            curr_word_idx++;
            word_turn = !(word_turn);
        } else {
            for (j=0; j<whsp_for_each_word; j++){
                buf[i] = ' ';
                i++;
            }
            if (extra_whsp) {
                buf[i] = ' ';
                i++;
                extra_whsp--;
            }
            word_turn = !(word_turn);
        }
    }
}

void print_center_word(char *word, int lineLength) {

    int word_len = strlen(word);
    int spaces = (lineLength - word_len) / 2;

    // print leading spaces
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }

    // print word
    printf("%s", word);

    // print trailing spaces
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }

    // account for if (lineLength - word_len) is odd, print at back of line
    if ((lineLength - word_len) % 2 == 1) {
        printf(" ");
    }
}


void formatAndPrintParagraph(char *paragraph, int lineLength)
{
    int i = 0;
    while (paragraph[i] == ' ')
        i++;

    char *para = paragraph + i;
    char *para_pointer = para;
    char *future_para_pointer = para;

    char lengths[MAX_WORDS]; // keeps track of length of each word
    char spbr_lengths[MAX_WORDS] = {0}; // to handle extra whitespaces from para (if there is)
    int word_cnt; // total count of words in para
    char buf[lineLength+1]; // the buffer to be printed

    int curr_word_idx = 0;
    int curr_ln_chars = 0;
    int start_word_idx = 0;
    int window_char_cnt;

    memset(lengths, 0, MAX_WORDS);
    word_cnt = word_count(para, lengths, spbr_lengths, lineLength);
    buf[lineLength] = '\0';



    if (word_cnt == 0) {
        print_center_word(paragraph, lineLength);
        return;
    }


    // justify algorthim
    while (lengths[curr_word_idx] != 0) {

        start_word_idx = curr_word_idx;
        window_char_cnt = 0;
        curr_ln_chars = 0;

        while ((lengths[curr_word_idx] != 0) &&
               (curr_ln_chars + (lengths[curr_word_idx] + 1) <= lineLength)) {
            curr_ln_chars += (lengths[curr_word_idx] + 1);
            window_char_cnt += lengths[curr_word_idx];
            future_para_pointer += lengths[curr_word_idx] + spbr_lengths[curr_word_idx];
            curr_word_idx++;
        }

        if ((curr_ln_chars + lengths[curr_word_idx]) == lineLength) {
            curr_ln_chars += lengths[curr_word_idx];
            window_char_cnt += lengths[curr_word_idx];
            future_para_pointer += lengths[curr_word_idx] + spbr_lengths[curr_word_idx];
            curr_word_idx++;
        }

        // create buffer to print
        write_to_buf(
                buf,
                lineLength,
                window_char_cnt,
                para,
                para_pointer,
                start_word_idx,
                curr_word_idx,
                lengths,
                spbr_lengths
        );
        printf("%s\n", buf);
        para_pointer = future_para_pointer;
    }
}

int main () {
    return 0;
}