#This program summs up the values of similar objects it  finds in a file
#Examplem, run -> perl object_sum_er.pl input.txt
#If it finds red:40 blue:10 red:5 yellow:2
#Will output red:45 blue:10 yellow:2

use English;

$filename=$ARGV[0]; #Gets input file
open(FH,"$filename"); #Opens file

my @setOfColors = <FH>; #stores the file into an array

#pattern to find ("any color":"number")
#pattern is color(any word), followed by :, between whitespace(0-infinite times), followed by a number
my $clrNum = '[a-zA-Z]+\s*:\s*\-?\d+';
#$str = "yellow  :5 red:7\n yellow: 896  yellow:5"; #tester for pattern
#print $str =~ $clrNum, "\n"; #Tester to see if pattern match(Will print 1 if true)
print "My original set of colors are:\n";
print @setOfColors,"\n"; #Tester to print the file exactly as written

my %colorStorage = (); #Hash that will store the color and its matching sum total of numbers 
my $currentColor; #Temporary variable to store current color
my $currentNumber; #Temporary variable to store the current number
my $clrAndNum; #Temporary variable to store both current color and number

foreach $setOfColors(@setOfColors)
{
  #While loop that will iterate through each matching pattern
  while ($setOfColors =~ m/($clrNum)/g) 
  {	
	#Separate colors and numbers without a colon(:)
	$clrAndNum = $1; #Stores both color and number match found as written in the original file
	$clrAndNum =~ m/([a-zA-Z]+)/; #Finds the color(any word) and stores just the word no spaces
	$currentColor = $1; #Stores the current color found in "currentColor"
	$clrAndNum =~ m/(\-?\d+)/; #Finds the number to matching color (any set of numbers together after the colon(:) without no space)
	$currentNumber = $1; #Stores the current number found to "currentNumber"
	
	#print "$currentColor $currentNumber \n"; #Test print color and matching number without colon
	
	#If the current color had a previous amount the new sum will be previous sum plus the new amount
	#If it doesn't then it will add 0 with the new amount
	$colorStorage{ $currentColor } = $currentNumber + $colorStorage{$currentColor};
  }
}

#Prints each color with its matching total value
print "My final set of summed colors are:\n";
for my $colors(keys %colorStorage) {  
	print "$colors : $colorStorage{$colors} \n";
}

close(FH); #Closes filehandle

#(C) YARLEY G, FREE TO USE
