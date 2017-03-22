#!/usr/bin/perl -w
## netchecker.pl for 42sh in /goinfre/grosli_o-42sh/test
##
## Made by olivier delestre
## Login   <delest_o@epita.fr>
##
## Started on  Sun Jan  9 16:28:55 2005 olivier delestre
## Last update Fri Jan 14 14:04:55 2005 olivier delestre
##

#################
#    HEADERS    #
#################
use strict;
use Getopt::Long;
use Term::ANSIColor qw(:constants);
Getopt::Long::Configure("no_auto_abbrev");

##################
# variables defs #
##################
my $user = $ENV{USER};
my $localdir = $ENV{PWD};
my $tarballdir = "grosli_o-42sh";
my $tarball = "grosli_o-42sh-1.tar.gz";

#############################
# variables defs for getopt #
#############################
my $us = 0;
my $outputdir = $localdir."/net-logs/`date +%Y-%m-%d-%Hh-%M`";
my $oh;
my $clean;
my $moulette;
my $compile;
my $file;
my $nologs;
my $i;

#  print usage of netchecker.pl  #
sub	print_usage{

    print RED, "\n     NetChecker for 42sh\n", RESET;
    print BLUE, "\n ./netchecker.pl -h HOSTS+ [OPTION]* [RULE] [--clean]\n", RESET;

    print YELLOW, "
  OPTIONS:\n", RESET;

print
"-o --outputdir    DIR
--help
--usage
--nolog\n";
print YELLOW "  RULE:\n", RESET;
print
"-m --moulette    OPTIONS
-c --compile
-f --file    FILE\n\n";
    exit(0);
}

# my getopt func
sub	my_getopt{

    GetOptions("usage|help" => \$us,
	       "o|outputdir=s" => \$outputdir,
	       "m|moulette" => \$moulette,
	       "c|compile" => \$compile,
	       "f|file=s" => \$file,
	       "h|host" => \$oh,
	       "clean" => \$clean,
	       "nolog|n|nologs" => \$nologs);
}

# test if str is an option or not
sub     is_opt{

    my $str = $_[0];
    my $var;

    $var = substr($str, 0, 1);
    if ($var eq "-"){
        return (1);
    }
    else{
        return (0);
    }
}

# get host from ARGV
sub     get_hosts{

    my $i = 0;
    my $oh = 0;
    my $nbhosts = 0;
    my @hosts;
    my $end = 0;

    while ($i < @ARGV && !$end){
	if ($ARGV[$i] eq "--host" || $ARGV[$i] eq "-h"){
            $oh=1;
        }
        elsif($oh){
	    if (!is_opt($ARGV[$i])){
		@hosts = (@hosts, $ARGV[$i]);
                $nbhosts++;
            }
	    else{
		$end = 1;
	    }
        }
        $i++;
    }

    if ($oh && $nbhosts < 1){
        print_usage();
    }

    return @hosts;
}

# get moulette options if they are specified
sub     get_mouli_opt{

    my $i = 0;
    my $mouliopt = "";

    while ($i < @ARGV){
	if ($ARGV[$i] eq "--moulette" || $ARGV[$i] eq "-m"){
            $moulette=1;
        }
        elsif($moulette){
	    if (!is_opt($ARGV[$i])){
		$mouliopt = $ARGV[$i];
	    }
	}
	$i++;
    }

    return $mouliopt;
}

# test if there is multiple rules -> print usage
sub	test_rules{

    if (($file && $compile) || ($file && $moulette) || ($moulette && $compile)){
	print_usage();
    }
    if (!$file && !$compile && !$moulette){
	print_usage();
    }
}

# func to compile the project on $host
sub	compile{

    my $host = $_[0];
    my $detaropt = "-zxvf";
    my $retour;
    
    print YELLOW, "Creating temporary directory on host $host ..\n", RESET;
    system ("ssh $host \"rm -rf /tmp/$user\"");
    system ("ssh $host \"mkdir /tmp/$user\"");
    system ("ssh $host \"chmod 700 /tmp/$user\"");

    print BLUE, "Copying tarball to temporary directory on host $host ..\n", RESET;
    system ("scp ../../$tarball $user\@$host:/tmp/$user");
    system ("ssh $host \"chmod 600 /tmp/$user/$tarball\"");

    print YELLOW, "Extracting tarball $tarball ..\n", RESET;
    system ("ssh $host \"cd /tmp/$user && tar $detaropt $tarball > /dev/null\"");

    print YELLOW, "Compiling the project on host $host ..\n", RESET;
    $retour = system ("ssh $host \"cd /tmp/$user/$tarballdir && ./configure && make clean all > compil-$host.log\"");
    $retour /= 256;
    if ($retour == 0){
	print GREEN, "Compilation finished succesfully...\n", RESET;
    }
    else{
	print RED, "Compilation exited abnormally with code $retour ...\n", RESET;
    }
    if (!$nologs){
	print YELLOW, "Making logs directory on localhost : $ENV{HOST} .. \n", RESET;
	system("if [ ! -d $outputdir ]; then
                mkdir $outputdir 2> /dev/null
                    fi");
	print BLUE, "Getting compilation log from host $host ...\n", RESET;
	system("scp $user\@$host:/tmp/$user/$tarballdir/compil-$host.log $outputdir/compil-$host.log");
    }
    return $retour;
}

# func to compile the project on $host and launch checker.pl on it
sub	moulette{

    my $host = $_[0];
    my $mouliopt = $_[1];
    my $retour;
    
    $retour = compile($host);
    if (!$retour){
	system ("ssh $host \"cd /tmp/$user/$tarballdir/test && ./checker.pl $mouliopt > ../mouli-$host.log\"");
	if (!$nologs){
	    print YELLOW, "Making logs directory on localhost : $ENV{HOST} .. \n", RESET;
	system("if [ ! -d $outputdir ]; then
                mkdir $outputdir 2> /dev/null
                    fi");
	    print BLUE, "Getting moulinette log from host $host ...\n", RESET;
	    system("scp $user\@$host:/tmp/$user/$tarballdir/mouli-$host.log $outputdir/mouli-$host.log");
	}
    }
}

#func to launch
sub	file{

    my $host = $_[0];
    my $env = "$ENV{HOME}/.ssh/environment";
    my $retour;
    
    $retour = compile($host);
    if ($retour == 0){
	system("ssh $host \"rm -f $env\"");
	system("ssh $host \"echo \"TARBALL_DIR=/tmp/$user/$tarballdir\" >> $env\"");
	system("ssh $host \"echo \"REMOTE_HOST=$ENV{HOST}\" >> $env\"");
	system("ssh $host \"echo \"TRACE_DIR=/tmp/$user/$tarballdir\" >> $env\"");
	system("ssh $host \"echo \"EXECDATE=\" >> $env\"");
	system ("ssh $host \"cd /tmp/$user/$tarballdir/test && $file\"");
    }
}

#################
# main function #
#################
sub	main{

    my @hosts;
    my $mouliopt;

    @hosts = get_hosts();
    $mouliopt = get_mouli_opt();
    my_getopt();

    if ( !$oh || $us){
	print_usage();
    }
    else{
	test_rules();
	print YELLOW, "Creating tarball $tarball on local machine : $ENV{HOST} ..\n", RESET;
	system ("cd .. && ./configure && make targz > /dev/null");
	if (!$nologs){
	    print YELLOW, "Making logs directory on localhost : $ENV{HOST} .. \n", RESET;
	    system("if [ ! -d $outputdir ]; then
                        mkdir $outputdir 2> /dev/null
                    fi");
	}
	
	for ($i = 0; $i < @hosts; $i++){
	    if ($compile){
		compile($hosts[$i]);
	    }
	    elsif($moulette){
		moulette($hosts[$i], $mouliopt);
	    }
	    else{
		file($hosts[$i]);
	    }
	    
	    if ($clean){
		print YELLOW, "Cleaning directory /tmp/$user on host $hosts[$i]\n", RESET;
		system("ssh $hosts[$i] \"rm -rf /tmp/$user\"");
	    }
	}
    }
    system("rm -f ../../$tarball");
}

main;
