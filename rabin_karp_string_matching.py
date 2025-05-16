hash_codes = {'a': 1, 'b': 2}

hash_codes = {
    'a': 1,  'b': 2,  'c': 3,  'd': 4,  'e': 5,
    'f': 6,  'g': 7,  'h': 8,  'i': 9,  'j': 10,
    'k': 11, 'l': 12, 'm': 13, 'n': 14, 'o': 15,
    'p': 16, 'q': 17, 'r': 18, 's': 19, 't': 20,
    'u': 21, 'v': 22, 'w': 23, 'x': 24, 'y': 25,
    'z': 26
}

fast_pow_10 = [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000]

haystack = str(input("Enter the haystack string:"))
needle = str(input("Enter the needle string:"))

needle_length = len(needle)
needle_code = 0

j = 0
for i in range(needle_length - 1, -1, -1):
    needle_code += fast_pow_10[i] * hash_codes[needle[j]]
    j += 1

print("needle code:", needle_code)

haystack_length = len(haystack)
if haystack_length >= needle_length:
    haystack_code = 0
    j = needle_length - 1
    for i in range(needle_length):
        haystack_code += fast_pow_10[j] * hash_codes[haystack[i]]
        j -= 1
    
    for i in range(1, haystack_length - (needle_length - 1)):
        if haystack_code == needle_code:
            print("String starts at index", i, "in haystack.")
            break
        elif i + needle_length < haystack_length:
            haystack_code = (haystack_code - (hash_codes[haystack[i - 1]] * fast_pow_10[needle_length - 1])) * 10 + hash_codes[haystack[i + needle_length]]
