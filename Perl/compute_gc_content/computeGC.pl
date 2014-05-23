#COMPUTES THE GC CONTENT OF A NEUCLOTIDE GIVEN FILE OR FILES AS ARGUMENTS
#
#Example -> to get the gc content of input0
#perl computeGC.pl input0.txt  -> Will get the GC Content of each input0.txt
#perl computeGC.pl input0.txt input1.txt - > Will get for each gene that it finds in input0.txt and input1.txt

use English;

#Stores all the files into an array
if (!@ARGV){die "No files or invalid files given";}
my @arrFiles = readAllFiles(@ARGV);

#pattern to find genes
my $pattern = "atg(([actg]{3})+?)(taa|tga|tag)";

#Prints the gc contents of each file only, seperated by one line
foreach $line (@arrFiles)
{
    print "The GC CONTENT OF\n$line\n";
    #If it finds at least one gene then it will check the entire line
    if ($line=~ m/$pattern/){
	#While loop which finds all matches and find  the g's and c's
        while ($line=~ m/$pattern/g){
        print "->$1 = ";
		print compute_gc_content($1),"% \n";
        }
    }   
    #Else print 0 since it has no gc content
    else {
    	print "0\n\n";
    }
    print"\n";
}



####################      FUNCTIONS      ######################

#Reads all files given as argument and returns them into an array
sub readAllFiles {
    my @allData;
    foreach $file(@_){
        open(FILE, "$file") or die "Invalid file! '$file' Please check for typos\n";
        my @currentFile = <FILE>;
        close(FILE);
		
		foreach $currLine(@currentFile){
			chomp($currLine);
            push (@allData, $currLine)
        }
	}
    return @allData;
}


#Calculates GC content of all the files given
sub compute_gc_content{
	#stores line of codons to $strand variable and process the GC content
	my $strand = $_[0];
	chomp($strand);

	my $gc = 0; #letter g and c counter
	my $neucloLen = 0; #length of gene
	my @foundGC= (); #Array to hold gc contents found
	
	foreach $char(split(//, $strand)) #for each character in the string we split
	{
		#If the character is a g or c our counter increases by 1
		if (($char eq 'g')||($char eq 'c')){
		$gc+=1;
		}			
	}
	#Length of the strand
	$neucloLen = length($strand);
	
	#If the gc content is 0	
	if ($gc =~ 0) {
		return 0;
	}
	
	#else if the $gc > 0 then it calculates the gc content
	else {
	return (($gc*100) / $neucloLen);
	}
}
