from cs50 import get_string

IN_WORD = 1
OUT_WORD = 0 

text = get_string("Text: ")

letters = words = sentences = cursor = 0

length = len(text)

cursor = OUT_WORD

for i in range(length):
    # Count letters and only letters 
    if text[i] < 'A' or text[i] > 'z':
        pass
    elif text[i] > 'Z' and text[i] < 'a':
        pass
    else:
        letters += 1
    
    # If cursor is a space, tab or newline, then assign cursor to out of a word 
    if text[i] == ' ' or text[i] == '\t' or text[i] == '\n':
        cursor = OUT_WORD
    # if text[i] is not a space, tab or newline then cursor is in_word.
    # If text[i] was previously a space, tab or newline, the last word had finished to words+=1
    elif cursor == OUT_WORD:
        cursor = IN_WORD
        words += 1
        
    if text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1

# print(letters)
# print(words)
# print(sentences)
    
index = 0.0
# The Coleman-Liay formula determines the grade level of a peice of text.
index = 0.0588 * (letters / words * 100.0) - 0.296 * (sentences / words * 100.0) - 15.8
    
rounded = round(index, 0)
    
# Determine what number round is and print the grade.
for i in range(length):
    if (rounded == i):
        print(f"Grade {i}")
        break
    elif rounded > 16:
        print("Grade 16+")
        break
    elif rounded < 1:
        print("Before Grade 1")
        break
        