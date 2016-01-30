#!/usr/local/bin/perl

printf "Transform txt knapsack in data ILP\n";
printf "";

my $old="$ARGV[0]";
my $new="$ARGV[1]";
my $error_write="Impossible to write in $new";

open(OLD, "<", $old)        or die "Impossible to open $old: $!";
open(NEW, ">", $new)        or die "Impossible to open $new: $!";

print NEW "data ;\n"	or die $error_write;

printf "->write items name ...\n";
print NEW "\nset I := "	or die $error_write;
while (<OLD>) {
	if ($. != 1) {
		my @values = split(' ');
		# print it[num] a[i]
		print NEW " it$values[0]"	or die $error_write;
	}
}
print NEW " ;\n"	or die $error_write;

close(OLD)     or die "Impossible to close $old: $!";
open(OLD, "<", $old)        or die "Impossible to reopen $old: $!";


printf "->write size parameters ...\n";

while (<OLD>) {
	my @values = split(' ');
	if ($. == 1) {
		print NEW "\nparam mi := $values[0];\n"	or die $error_write;		

		print NEW "\nparam a := "	or die $error_write;
	} else  {
		# print it[num] a[i]
		print NEW "\n\tit$values[0] \t$values[1]"	or die $error_write;
	}
}
print NEW " ;\n"	or die $error_write;

close(OLD)     or die "Impossible to close $old: $!";
open(OLD, "<", $old)        or die "Impossible to reopen $old: $!";

printf "->write profit parameters ...\n";

while (<OLD>) {
	my @values = split(' ');
	if ($. == 1) {
		print NEW "\nparam mw := $values[1];\n"	or die $error_write;		

		print NEW "\nparam c := "	or die $error_write;
	} else  {
		# print it[num] c[i]
		print NEW "\n\tit$values[0] \t$values[2]"	or die $error_write;
	}
}
print NEW " ;\n"	or die $error_write;

print NEW "\nend;\n"	or die $error_write;

# Close files
close(OLD)     or die "Impossible de close $old: $!";
close(NEW)     or die "Impossible de close $new: $!";

printf "DONE\n";

