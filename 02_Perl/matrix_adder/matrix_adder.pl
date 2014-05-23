#This program adds 2 matrices which are the same size together
#Example, run -> perl matrix_adder.pl input0.txt input1.txt output.txt
#input0.txt   input1.txt  output.txt
# 0 1 2         1 1 2       1 2 4
# 2 1 0     +   1 0 6   =   3 1 6
# 3 5 6         2 3 3       5 8 9
#
#The matrices must be given in 2 seperate files and the answer will be placed in the 3rd argument the user placed (the output file)

use English;
open(M1,"$ARGV[0]") or die "Invalid first input file given"; #Matrix 1 file input
open(M2,"$ARGV[1]") or die "Invalid second input file given"; #Matrix 2 file input
open(MO,">$ARGV[2]") or die "Error. No output file given"; #Matrix sum file output

my @mat_1 = <M1>; #First matrix from file into array;
my @mat_2 = <M2>; #Second matric from file into array;

#Cleans array and stores it back to the original array as a 2dimension matrix ($
@mat_1 = clean_matrix(@mat_1);
@mat_2 = clean_matrix(@mat_2);

#If the matrices are equal in size (Ex..(2x3==2x3, 2x3!=3x2) or 3x3==3x3 3x3!=4x4))
if(are_equal(\@mat_1, \@mat_2)) {
        #This function will sum the 2 matrices to a new matrix
        @summed_matrix = add_matrices(\@mat_1, \@mat_2); #Adds the matrices

        #PRINTS OUT THE ADDENDS MATRICES AND SUMMED MATRIX TO FILE
        print MO "THE SUM OF \nMATRIX 1 + MATRIX 2 = MATRIX 3\n\nMATRIX1\n";
        prints_summed_tofile(\@mat_1, \@mat_2, \@summed_matrix);
}

#Else the addend matrices aren't the same size, therefore can't add
else 
{
        print "Matrix 1 and Matrix 2 are not of the same size.\n";
        print "----- > TRY ANOTHER SET OF 2 MATRICES < -----!\n";
	print MO "Matrix 1 and Matrix 2 are not of the same size.\n";
        print MO "----- > TRY ANOTHER SET OF 2 MATRICES < -----!\n";

}



#####################   ->     FUNCTIONS   <-    ######################


#Returns the file as a 2 dimensional matrix without no whitespaces which can be accessed as array[i][j]
sub clean_matrix{
	my @clean_matrix_arr; #Array to store matrix read from file
	my $i=0;
	foreach $line(@_){
		chomp($line); #Rids of last line
		$line =~ s/^\s+//g; #Rids of whitespace in the beginning
		push(@clean_matrix_arr, [split(/\s+/,$line)]) #Creates row dimension of 2x2,3x3,...FxF array
	}
	return @clean_matrix_arr;
}


#Test to see if 2 matrices are equal
sub are_equal{
	my ($firstmat, $secondmat) = @_; #Sets both matrices to 2 different referent arrays

	#Stores the sizes of each row of the first matrix to a temp array
	foreach $line(@$firstmat) { 
		$line_size = @$line;
		push(@first_2d_arr, $line_size)
	}
	
	#Stores the sizes of each row of the second matrix to another temp array
	foreach $line(@$secondmat) {
		$line_size = @$line;
		push(@second_2d_arr, $line_size)
	}
	
	#If the first matrix don't have the same amount of rows as the second, then they're not equal
	$first_arr_size = @first_2d_arr;
	$second_arr_size = @second_2d_arr;
	if ($first_arr_size != $second_arr_size){
		return 0;
	}

	#Else will test each corresponding row of each matrix to see if they're the same size
	else 
	{	
		#If it reaches here then both matrices have same number of rows
		#This will test if the size of each corresponding row are the same	
		#Could use the size of the first or second array for the array loop since they're both equal	
		for ($i=0;$i<@first_2d_arr;$i++){
			if ($first_2d_arr[$i] != $second_2d_arr[$i]){
				return 0;
			}
		}

		#for ($i=0;$i<@second_2d_arr;$i++){
                #        if ($first_2d_arr[$i] != $second_2d_arr[$i]){
                #                return 0;
                #        }
         	#}	
		return 1; #If it can reach here there the matrices are the same size
	}

}


#Adds 2 matrices and returns the summed matrix
sub add_matrices{
	my ($firstmat, $secondmat) = @_; #Sets both matrices to 2 different ref$
	@first_mat = @$firstmat; #First Matrix
	@sec_mat = @$secondmat; #Second Matrix
	my @summed_mat=(); #Summed Matrix
	my $i=0; #iterator for rows

        #For each row in both matrices it will add their equivalent coordinates and push it to the new matrix
        foreach $row(@first_mat)
	{
		my @summed_row=(); #Stores temporary sum for each row, resets everytime $i increments
		for ($j=0;$j<@$row;$j++){
			push(@summed_row, ($first_mat[$i][$j] + $sec_mat[$i][$j]));
		}
                push(@summed_mat, [@summed_row]);
		$i++;
        }
	return @summed_mat;
}


#Prints a given matrix (as an 2 dimensional array) to file
sub print_thematrix_tofile{
	foreach $row(@_){
		foreach $number(@$row){
			print MO $number," ";
		}
		print MO "\n";
	}
	print MO "\n";
}

#Prints the sum of the matrices and its addends
sub prints_summed_tofile {
	my ($firstmat, $secondmat, $summat) = @_;
	print_thematrix_tofile(@$firstmat),"\n";
        print MO "   + \n\nMATRIX 2\n";
        print_thematrix_tofile(@$secondmat),"\n";
        print MO "   =\n\nMATRIX 3\n";
        print_thematrix_tofile(@$summat),"\n";
}


close(M1); # closes Matrix 1 file handle
close(M2); # closes Matrix 2 file handle
close(MO); # closes Matrix output with the sum file handle

#(C) YARLEY G, FREE TO USE
