string = 'abcdefghijklm'
for i in range(0, 12, 4):
    print(string[i:i+4])
    

def check_dna(sample, nucleotides):
    nucleotides_copy = copy.deepcopy(nucleotides)
    nucleotides_list = copy.deepcopy(list(nucleotides))
    # check all necleotides with 5 chars 
    for i in range(0, len(sample), 5):
        print(sample[i:i+5])
        
        if nucleotides_list[0] == sample[i:i+5]:
            print('hi')
            
            for j in range(i, len(sample), 5):
                if nucleotides_list[0] == sample[j:j+5]:
                    nucleotides_copy[nucleotides_list[0]] += 1
            
            for key in nucleotides:
                tmp_nucleotides = copy.deepcopy(nucleotides)
            
                if tmp_nucleotides[key] < nucleotides_copy[key]:
                    nucleotides[key] = nucleotides_copy[key]
                    
    return nucleotides_copy
    
