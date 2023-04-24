////////******************FOR DES *********************///////////////

In DES , first I have used a 64 bit plaintext applying initial permutation. Then divided plaintext into two 32 bits parts
, after that I have used fiestel function for feistel structre. Here we need key
keys are generated from key_schedule function  . We used the getbit and setbit concept.There are temp_key_1 and temp_key_2
for storing 56 bit key and then after rotating applied PC2 to get all roundkeys that are stored globally'
These roundkeys are XORed with expansion R0 and after going through sbox ,process is repeated for 16 rounds.
For decryption same key_schedule() is used just in reverse direction.    
//////////****************FOR CFB*******************//////////////


At first  DES part  is used as a block cipher mode encryption and this is already described in DES IMPLEMENTATION.
In the Main function 
I have done to take input from a file ,named "message.txt" and it is allowed to read from starting to the end of the file.
The I have done padding.
I have created spaces for plaintext and cipher text and store after reading from file into plaintext.
I have printed 0 in padded bit.
In encryption ,I have taken as input as plaintext and paded size , and IV and then applied DES on IV first and then xored with plaintext 1st block and the output is used as a feedback for next round. atlast we have output all the cipher. 
Decryption of CFB is same as Encryption
