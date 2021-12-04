from sys import argv
import csv
import copy

def main():
    if len(argv) != 3:
        print("Usage: python dna.py database DNA")
        return

    database = argv[1]
    DNA = argv[2]

    suspects = []
    with open(database, "r") as db:
        reader = csv.DictReader(db)

        for row in reader:
            suspects.append(row)


    with open(DNA, "r") as evidence:
        for line in evidence:
            # proof is the sequence of DNA
            sample = line.rstrip()

    nucleotides = types_of_dna(suspects)
    nucleotides = check_dna(sample, nucleotides)
    # print(nucleotides)

    # Change the key: values for every suspect into an integer
    for suspect in range(len(suspects)):
        for key in suspects[suspect]:
            try:
                suspects[suspect][key] = int(suspects[suspect][key])
            except:
                suspects[suspect][key] = suspects[suspect][key]

    # Create a deep copy of the suspects
    suspects_copy = copy.deepcopy(suspects)

    # Remove the key 'name' from suspects_copy. for nucleotide comparison
    for i in range(len(suspects)):
        del suspects_copy[i]['name']

    found = ""
    # compare dna_types to suspects_copy
    for i in range(len(suspects)):
        # nucleotides is a dictionary and suspects_copy is a list of dictionaries
        if nucleotides == suspects_copy[i]:
            # Print the name of suspect
            found = suspects[i]['name']
            print(found)
            break
        else:
            pass

    if found == "":
        print("No match")


# This function returns a dictionary for all types of possible DNAs
def types_of_dna(suspects):
    typeDNA = suspects[0].keys()
    typeDNA = list(typeDNA)
    typeDNA.remove('name')

    dna_types = {}
    for dna in typeDNA:
        dna_types[dna] = 0

    return dna_types


def check_dna(sample, nucleotides):
    # Simply add a new elif for any additional nucleotide checks
    for dna in nucleotides:
            if dna == 'AGATC':
                nucleotides[dna] = count_dna(sample, dna)
            elif dna == 'TTTTTTCT':
                nucleotides[dna] = count_dna(sample, dna)
            elif dna == 'AATG':
                nucleotides[dna] = count_dna(sample, dna)
            elif dna == 'TCTAG':
                nucleotides[dna] = count_dna(sample, dna)
            elif dna == 'GATA':
                nucleotides[dna] = count_dna(sample, dna)
            elif dna == 'TATC':
                nucleotides[dna] = count_dna(sample, dna)
            elif dna == 'GAAA':
                nucleotides[dna] = count_dna(sample, dna)
            elif dna == 'TCTG':
                nucleotides[dna] = count_dna(sample, dna)

    return nucleotides


def count_dna(sample, dna):
    # Length of nucleotide and sample
    nuc_len = len(dna)
    samp_len = len(sample)
    # The final count.
    final_count = 0
    # from start of sample to end of sample
    for i in range(0, samp_len):
        count = 0
        # If dna is in sample[nucleotide length]
        if dna == sample[i:i+nuc_len]:
            # from that point count every nucleotide length
            for j in range(i, samp_len, nuc_len):
                # if dna is in the nucleotide length of sample
                if dna == sample[j:j+nuc_len]:
                    count += 1
                    # If count is larger than final count.
                    if count > final_count:
                        final_count = count
                else:
                    break
    return final_count


if __name__ == "__main__":
    main()