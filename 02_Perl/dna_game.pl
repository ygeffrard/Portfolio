#DNA GAME which generates a random gene, with a length given by the user and the user must translate to RNA

print "RNA POLYMERASE.\n";
print "\nEnter the number of nucleotides in the strand (must be more than 0)\n\n";

my $dnaLength = <STDIN>; #user input number of DNA strings they want
chomp($dnaLength); #Removes \n

while (($dnaLength !~ /^[+-]?\d+$/) || ($dnaLength < 1)) #user will have to try again if the input wasn't all numbers
{
print "Try again. You can only enter a number greater than 1 : ";
$dnaLength = <STDIN>; #Ask input from user again
chomp($dnaLength);
print "\n";
}


#DNA hashtable Class symbols to match random numbers generated from 1-4 to corresponding DNA strand
%dnaClass=
(
	1 => 'a',
	2 => 't',
	3 => 'c',
	4 => 'g'
);


#RNA from DNA converting hash table
%rnaClass = (
	u => 'a',
        a => 't',
        g => 'c',
        c => 'g'
);


my @myDNA = (); #will hold actual DNA string
my @myRNA = (); #list to store RNA
my $dnaNum; #Variable to store each individual number generated to be converted to a DNA string


#For-loop that will get random generated DNA strands to form DNA string and also RNA strands
for (my $i=0; $i < $dnaLength; $i++)
{
$dnaNum = int(rand(4)+1);
push (@myDNA, $dnaClass{$dnaNum}); 
}

my $matchDNA; #Value for RNA strand input and "q"
my $match=0; #iterator
my @updateRNA = (); #store updating RNA strings
my @doneDNA = (); #DNA strands converted
my @remDNA = @myDNA; #DNA strands remaining
shift (@remDNA); #The first time DNA strand remaining is show, the first one has to be removed because it's displayed as the first DNA to match

#While loop to iterate through each DNA strand to match to RNA strand, then ask user for correct match
while ( ($match < $dnaLength) && ($matchDNA ne 'q') )
{
print "DNA: ", @doneDNA, "  ->  ", $myDNA[$match], "  <-  ", @remDNA, "\nRNA: ", @updateRNA, "\n";
print "What matches this  nucleotide? (press 'q' to exit)\n";
$matchDNA = <STDIN>;
chomp($matchDNA);
	if ($matchDNA eq 'q') {
	print "You have exited. Play again soon!\n";
	last;
	}

	elsif ($rnaClass{$matchDNA} ne $myDNA[$match])
        {
	print "\nNot the correct corresponding value. Try Again!\n";
        }

	else {
	push (@updateRNA, $matchDNA);
	shift (@remDNA);
	push (@doneDNA, $myDNA[$match]);
	$match +=1;
	print "Correct!\n\n";
	}
}

if ($matchDNA ne 'q')
{
print "Congratulations! You've succesfully transcribe DNA : ", @myDNA, " to\nRNA : ", @updateRNA, "\n";
}

