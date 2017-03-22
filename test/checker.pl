#!/usr/bin/perl -w
## checker.pl for checker in /u/a1/raymon_e
##
## Made by enguerrand raymond
## Login   <raymon_e@epita.fr>
##
## Started on  Sun Jan  9 11:00:14 2005 enguerrand raymond
## Last update Tue Jan 18 20:26:38 2005 olivier delestre
##

use strict;
use Getopt::Long;

#####################################################################
##								   ##
##                           VALUES				   ##
##								   ##
#####################################################################

#
## sh42 -> shell against shell reference(bash).
#
my $sh42;

#
## value to the command line's options.
#
my $categorie;
my $selects;
my @select;
my $final;
my $number;
my $all;
my $save;
my $load;
my $isbetter;
my @better;
my $timeout;

#
## $timeouted -> value used to the timeout tolerance.
#
my $timeouted = 1;

#
## pid -> pid of child that execute the bash [test file]
##	  and sh42 [test file].
#
my $pid;

#
## nbr_test -> Number of test write for the moment
##	       value not definitive.
#
my $nbr_test = 0;

#
## Value to the evaluation of test percents
##
## nbr_win     -> number of test wins.
## nbr_failed  -> number of test failed.
## nbr_rep     -> number of test in the current categorie.
## nbr_sg      -> number of segfault test.
## nbr_bi      -> number of inifinite loop.
## nbr_wrep    -> number of test win by categorie.
## nbr_res     -> final result (percent or number).
## nbr_sgresol -> number of sg resolv.
## nbr_sgrep   -> number of sg by folder.
#
my $nbr_win = 0;
my $nbr_failed = 0;
my $nbr_rep = 0;
my $nbr_wrep = 0;
my $nbr_seg = 0;
my $nbr_bi = 0;
my $nbr_sgresol = 0;
my $nbr_sgresol2 = 0;
my $nbr_frep = 0;
my $nbr_sgrep = 0;
my $nbr_teste = 0;
my $nbr_totf = 0;
my $nbr_totw = 0;
my $nbr_totsg = 0;
my $nbr_totbi = 0;
my $nbr_segprec = 0;
my $disp=0;

#
## Function to detect the presence of command line's options
## and recuperate the arguments.
#
Getopt::Long::Configure("no_auto_abbrev");
GetOptions( "c|categories" => \$categorie, "s|save=s" => \$save, "e|select=s" => \$selects,
	    "f|final" => \$final, "n|number" => \$number, "a|all" => \$all, "l|load=s" => \$load,
	    "i|isbetter=s" => \$isbetter, "t|timeout=i" => \$timeout, "w" => \$disp);
$sh42=shift;
if (!$sh42)
{
    $sh42 = '../42sh';
}

#####################################################################
##								   ##
##                           SOURCE CODE			   ##
##								   ##
#####################################################################

#
## Function that test if the option timeout
## is add inthe moulinette called and change
## this value.
##
## Called by -> the script's beginning.
#
sub ctimeout
{
    if ($timeout)
    {
	$timeouted = $timeout;
    }
}

#
## Recursive function for the test tree travel.
## We use the incredible property of the function glob
## this function by globing give the files and folders
## of current folder in a array.
##
## Called by -> the script's beginning.
## Calls     -> test.
## Calls     -> call_test.
## Calls     -> is_file.
#
sub parcour
{
  my $dossier = shift;
  my $categorie2 = shift;
  my @tab;
  my $file;
  my $i;
  my $percent;

  $nbr_rep = 0;
  $nbr_wrep = 0;
  $nbr_sgresol = 0;
  $nbr_frep = 0;
  $nbr_sgrep = 0;
  display_categorie($dossier);
  opendir(REP, $dossier);
  while ($file = readdir(REP))
  {
      @tab = (@tab, $file);
  }
  for ($i = 0; $i < @tab; ++$i)
  {
      if ((-f $dossier."/".$tab[$i]) && ($tab[$i]  =~ /.test/))
      {
	  if ($isbetter)
	  {
	      if (is_categorie($dossier))
	      {
		  ++$nbr_rep;
		  ++$nbr_test;
		  if (is_categorie($dossier))
		  {
		      test($dossier."/".$tab[$i], $tab[$i], $dossier);
		  }
	      }
	  }
	  else
	  {
	      ++$nbr_rep;
	      ++$nbr_test;
	      if (is_categorie($dossier))
	      {
		  test($dossier."/".$tab[$i], $tab[$i], $dossier);
	      }
	  }
      }
  }
  if (is_file($dossier) == 1)
  {
      if (!$final && is_categorie($dossier))
      {
	  if ($number)
	  {
	      if ($categorie)
	      {
		  categ($dossier);
	      }
	      else
	      {
		  if ($isbetter)
		  {
		      print "\n\033[31mTests reussis \033[0m    [ \033[32m$nbr_wrep/$nbr_rep\033[0m ]\n";
		      print "\033[31mTests rates \033[0m      [ \033[32m$nbr_frep/$nbr_rep\033[0m ]\n";
		      print "\033[31mSeg-fault resolus \033[0m[ \033[32m$nbr_sgresol/$nbr_sgrep\033[0m ]\n\n";
		  }
		  else
		  {
		      print "\n\033[31mTests reussis \033[0m[ \033[32m$nbr_wrep/$nbr_rep\033[0m ]\n\n";
		  }
	      }
	  }
	  else
	  {
	      if ($categorie)
	      {
		  categ($dossier);
	      }
	      else
	      {
		  if ($isbetter)
		  {
		      $percent = sprintf("%.0f", ($nbr_wrep * 100) / $nbr_rep);
		      print "\n\033[31mTests reussis \033[0m    [ \033[32m$percent%\033[0m ]\n";
		      $percent = sprintf("%.0f", ($nbr_frep * 100) / $nbr_rep);
		      print "\033[31mTests echoues \033[0m    [ \033[32m$percent%\033[0m ]\n";
		      $percent = 0;
		      if ($nbr_sgrep != 0)
		      {
			  $percent = sprintf("%.0f", ($nbr_sgresol * 100) / $nbr_sgrep);
		      }
		      print "\033[31mSeg-fault resolus \033[0m[ \033[32m$percent%\033[0m ]\n\n";
		  }
		  else
		  {
		      $percent = sprintf("%.0f", ($nbr_wrep * 100) / $nbr_rep);
		      print "\n\033[31mTests reussis \033[0m[ \033[32m$percent%\033[0m ]\n\n";
		  }
	      }
	  }
      }
      if ($save)
      {
	  if ($number)
	  {
	      print SAVEF "\n\033[31mTests reussis \033[0m[ \033[32m$nbr_wrep/$nbr_rep\033[0m ]\n\n";
	  }
	  else
	  {
	      $percent = sprintf("%.0f", ($nbr_wrep * 100) / $nbr_rep);
	      print SAVEF "\n\033[31mTests reussis \033[0m[ \033[32m$percent%\033[0m ]\n\n";
	  }
      }
  }
  for ($i = 0; $i < @tab; ++$i)
  {
      if (-d $dossier."/".$tab[$i])
      {
	  if (($tab[$i] ne ".") && ($tab[$i] ne "..") && ($tab[$i] ne "CVS"))
	  {
	      parcour($dossier."/".$tab[$i], $categorie2."->".$tab[$i]);
	  }
      }
  }
  close(REP);
}

#
## Display the categorie with option --categorie -c
##
## Called by -> parcour.
#
sub categ
{
    my $dossier = shift;
    my $percent;
    my $categ;
    my $i;

    $categ = $dossier;
    $categ =~ s/.\///;
    $categ =~ s/\///;
    $categ =~ s/\//->/g;
    if ($number)
    {
	print "\033[31mCategorie \033[0m[ \033[32m$categ \033[0m]\n";
	print "\033[31mTests reussis\033[0m [ \033[32m$nbr_wrep/$nbr_rep\033[0m ]\n";
	print "\033[31mTests echoues\033[0m [ \033[32m$nbr_frep/$nbr_rep\033[0m ]\n";
	if ($isbetter)
	{
	    print "\033[31mSeg-fault resolus\033[0m [ \033[32m$nbr_sgresol/$nbr_sgrep\033[0m ]\n\n\n";
	}
	else
	{
	    print "\n";
	}
    }
    else
    {
	$percent = sprintf("%.0f", ($nbr_wrep * 100) / $nbr_rep);
	print "\033[31mCategorie \033[0m[ \033[32m$categ \033[0m]\n";
	print "\033[31mTests reussis \033[0m[ \033[32m$percent%\033[0m ]\n";
	$percent = sprintf("%.0f", ($nbr_frep * 100) / $nbr_rep);
	print "\033[31mTests echoues \033[0m[ \033[32m$percent%\033[0m ]\n";
	if ($isbetter)
	{
	    if ($nbr_sgrep)
	    {
		$percent = sprintf("%.0f", ($nbr_sgresol * 100) / $nbr_sgrep);
	    }
	    else
	    {
		$percent = 0;
	    }
	    print "\033[31mSeg-fault resolus\033[0m [ \033[32m$percent%\033[0m ]\n\n\n";
	}
	else
	{
	    print "\n";
	}
    }
}

#
## Function called by parcour for the recursive called.
## Dislpays the categorie if the folder is filled fo test files.
##
## Called by -> parcour.
## Calls     -> is_file.
#
sub display_categorie
{
    my $dossier = shift;
    my $dossier2 = $dossier;

    if (!$categorie && !$final && is_categorie($dossier))
    {
	if (is_file($dossier) == 1)
	{
	    $dossier =~ s/.\///;
	    $dossier =~ s/\///;
	    if ($dossier)
	    {
		$dossier =~ s/\//->/g;
		print "\033[31mCategorie\033[0m [ \033[32m$dossier\033[0m ]\n\n";
	    }
	}
    }
    if ($save && (is_file($dossier2) == 1))
    {
	$dossier =~ s/.\///;
	$dossier =~ s/\///;
	if ($dossier)
	{
	    $dossier =~ s/\//->/g;
	    print SAVEF "\033[31mCategorie\033[0m [ \033[32m$dossier\033[0m ]\n\n";
	}
    }
}

#
## Says if the folder $folder is filled of test file.
##
## Called by -> dipslay_categorie.
## Called by -> parcour.
#
sub is_file
{
    my $folder = shift;
    my $file;
    my $res = 0;

    opendir(REP, $folder);
    while ($file = readdir(REP))
    {
	if ((-f $folder."/".$file) && ($file =~ /.test/))
	{
	    $res = 1;
	}
    }
    close(REP);
    $res;
}

#
## Function that executes the commands in test file.
## Bash is called and receive the test file in argument.
##
## Called by -> parcour.
## Calls     -> eval_res.
#
sub test
{
    my $file = shift;
    my $test = shift;
    my $dossier = shift;
    my $code_err = 0;

    if (!($pid = fork))
    {
	local $SIG{'ALRM'} = sub {die "je me meurs\n";};
	alarm $timeouted;
	open(STDOUT, "> rep_res/stdout_bash");
	open(STDERR, "> rep_res/stderr_bash");
	exec "bash $file";
    }
    waitpid($pid, 0);
    if (!($pid = fork))
    {
	local $SIG{'ALRM'} = sub {die "je meurs\n";};
	alarm $timeouted;
	open(STDOUT, "> rep_res/stdout_42sh");
	open(STDERR, "> rep_res/stderr_42sh");
	exec "$sh42 $file";
    }
    waitpid($pid, 0);
    $code_err = $?;
    system("diff rep_res/stdout_bash rep_res/stdout_42sh > rep_res/diff_stdout");
    eval_res($file, $code_err, $dossier);
    unlink('rep_res/stdout_bash', 'rep_res/stdout_42sh', 'rep_res/stderr_bash',
	   'rep_res/stderr_42sh', 'rep_res/diff_stdout', 'rep_res/code_retour');
}

#
## Function used to evaluate the test's result.
##
## called by -> test.
## Calls     -> display.
#
sub eval_res
{
    my $file = shift;
    my $code_err = shift;
    my $dossier = shift;
    my @file_desc;
    my $i=0;

    open(DESC, "<$file");
    @file_desc = <DESC>;
    if ($disp)
    {
	print "\n";
	for ($i = 3; $i < @file_desc; ++$i)
	{
	    print "$file_desc[$i]\n";
	}
    }
    chop $file_desc[1];
    $file_desc[1] =~ s/\#//;
    if ($code_err  == 14)
    {
	if ($save)
	{
	    print SAVEF "$file_desc[0]1\n\n";
	}
	if ($isbetter)
	{
	    while (($better[$i] !~ /^\#/) || ($file_desc[0] ne $better[$i]))
	    {
		++$i;
	    }
	    eval_diff('1', $better[$i+1], $file_desc[1], '', '', $dossier);
	}
	else
	{
	    display('TO', $file_desc[1], '', $dossier);
	}
    }
    else
    {
	if (($code_err != 0) && (($code_err % 128) == 11))
	{
	    if ($save)
	    {
		print SAVEF "$file_desc[0]2\n\n";
	    }
	    if ($isbetter)
	    {
		while (($better[$i] !~ /^\#/) || ($file_desc[0] ne $better[$i]))
		{
		    ++$i;
		}
		eval_diff('2', $better[$i+1], $file_desc[1], $better[$i+2], '', $dossier);
	    }
	    else
	    {
		display('SG', $file_desc[1], '', $dossier);
	    }
	}
	else
	{
	    if ((-z "./rep_res/diff_stdout"))
	    {
		if (((-z "rep_res/stderr_bash") && (-z "rep_res/stderr_42sh")) ||
		    (!(-z "rep_res/stderr_bash") && !(-z "rep_res/stderr_42sh")))
		{
		    if ($save)
		    {
			print SAVEF "$file_desc[0]4\n\n";
		    }
		    if ($isbetter)
		    {
			while (($better[$i] !~ /^\#/) || ($file_desc[0] ne $better[$i]))
			{
			    ++$i;
			}
			eval_diff('4', $better[$i+1], $file_desc[1], $better[$i+2], '', $dossier);
		    }
		    else
		    {
			display('OK', $file_desc[1], '', $dossier);
		    }
		}
		else
		{
		    if ($save)
		    {
			print SAVEF "$file_desc[0]3\nStderr differents!\n";
		    }
		    if ($isbetter)
		    {
			while (($better[$i] !~ /^\#/) || ($file_desc[0] ne $better[$i]))
			{
			    ++$i;
			}
			eval_diff('3', $better[$i+1], $file_desc[1], $better[$i+2], 'Stderr differents!', $dossier);
		    }
		    else
		    {
			display('KO', $file_desc[1], 'Stderr differents!', $dossier);
		    }
		}
	    }
	    else
	    {
		if ($save)
		{
		    print SAVEF "$file_desc[0]3\nStdout differents!\n";
		}
		if ($isbetter)
		{
		    while (($better[$i] !~ /^\#/) || ($file_desc[0] ne $better[$i]))
		    {
			++$i;
		    }
		    eval_diff('3', $better[$i+1], $file_desc[1], $better[$i+2], 'Stdout differents!', $dossier);
		}
		else
		{
		    display('KO', $file_desc[1], 'Stdout differents!', $dossier);
		}
	    }
	}
    }
    close DESC;
}

#
## Function to evaluate the difference beetwin
## the trace and the save. For the option --isbetter -i
##
## Called by -> eval_res.
#
sub eval_diff
{
    my $new_res = shift;
    my $save_res = shift;
    my $file_desc = shift;
    my $save_msg = shift;
    my $new_msg=shift;
    my $dossier=shift;

    if (!$save_msg)
    {
	$save_msg  = '';
    }
    if (!$new_msg)
    {
	$new_msg  = '';
    }
    chop $save_res;
    chop $save_msg;
    if ($new_res eq $save_res)
    {
	if ($save_res eq '4')
	{
	    display('++', $file_desc, '', $dossier);
	}
	else
	{
	    if ($save_res eq '1')
	    {
		++$nbr_bi;
	    }
	    if ($save_res eq '2')
	    {
		++$nbr_sgrep;
		++$nbr_segprec;
		++$nbr_seg;
	    }
	    display('--', $file_desc, $save_msg, $dossier);
	    ++$nbr_frep;
	}
    }
    else
    {
	if ($save_res eq '4')
	{
	    if ($new_res eq '2')
	    {
		display('OO', $file_desc, '', $dossier);
		++$nbr_sgrep;
		++$nbr_seg;
	    }
	    else
	    {
		if ($new_res eq '1')
		{
		    ++$nbr_bi;
		}
		else
		{
		    display('KO', $file_desc, $new_msg, $dossier);
		}
	    }
	    ++$nbr_frep;
	}
	else
	{
	    if ($save_res eq '2')
	    {
		++$nbr_sgrep;
		++$nbr_segprec;
		++$nbr_sgresol;
		++$nbr_sgresol2;
	    }
	    display('OK', $file_desc, '', $dossier);
	}
    }
}

#
## Displays the test's result with OK or KO.
##
## Called by -> eval_res.
## Calls     -> is_categorie.
#
sub display
{
    my $OK = shift;
    my $file_desc = shift;
    my $msg = shift;
    my $dossier=shift;
    my $i;

    if (!$categorie && is_categorie($dossier))
    {
	if (!$final)
	{
	    print "  \033[36m$file_desc\033[0m ";
	}
    }
    if ($save)
    {
	print SAVEF "  \033[36m$file_desc\033[0m ";
    }
    for ($i = 0; $i < (60 - length($file_desc)); ++$i)
    {
	if (!$categorie && is_categorie($dossier))
	{
	    if (!$final)
	    {
		print ' ';
	    }
	}
	if ($save)
	{
	    print SAVEF ' ';
	}
    }
    if ($OK eq 'OK')
    {
	++$nbr_totw;
	++$nbr_wrep;
	if (is_categorie($dossier))
	{
	    ++$nbr_win;
	    ++$nbr_teste;
	    if (!$categorie)
	    {
		if (!$final)
		{
		    print "[\033[32m $OK \033[0m]\n";
		}
	    }
	}
	if ($save)
	{
	    print SAVEF "[\033[32m $OK \033[0m]\n";
	}
    }
    else
    {
	if ($OK eq 'SG')
	{
	    ++$nbr_totf;
	    ++$nbr_totsg;
	    ++$nbr_sgrep;
	    if (is_categorie($dossier))
	    {
		++$nbr_seg;
		++$nbr_failed;
		++$nbr_teste;
		if (!$isbetter)
		{
		    ++$nbr_frep;
		}
		if (!$categorie)
		{
		    if (!$final)
		    {
			print "[\033[35m $OK \033[0m]\n";
		    }
		}
	    }
	    if ($save)
	    {
		print SAVEF "[\033[35m $OK \033[0m]\n";
	    }
	}
	else
	{
	    if ($OK eq 'TO')
	    {
		++$nbr_totbi;
		++$nbr_totf;
		if (is_categorie($dossier))
		{
		    ++$nbr_teste;
		    ++$nbr_bi;
		    ++$nbr_failed;
		    if (!$isbetter)
		    {
			++$nbr_frep;
		    }
		    if (!$categorie)
		    {
			if (!$final)
			{
			    print "[\033[33m $OK \033[0m]\n";
			}
		    }
		}
		if ($save)
		{
		    print SAVEF "[\033[33m $OK \033[0m]\n";
		}
	    }
	    else
	    {
		if ($OK eq 'KO')
		{
		    ++$nbr_totf;
		    if (is_categorie($dossier))
		    {
			++$nbr_failed;
			++$nbr_teste;
			if (!$isbetter)
			{
			    ++$nbr_frep;
			}
			if (!$categorie)
			{
			    if (!$final)
			    {
				print "[\033[31m $OK \033[0m] \033[31m$msg\033[0m\n";
			    }
			}
		    }
		    if ($save)
		    {
			print SAVEF "[\033[31m $OK \033[0m] \033[31m$msg\033[0m\n";
		    }
		}
		else
		{
		    if ($OK eq '++')
		    {
			if (is_categorie($dossier))
			{
			    ++$nbr_win;
			    ++$nbr_wrep;
			    ++$nbr_teste;
			    if (!$categorie)
			    {
				if (!$final)
				{
				    print "[\033[32m $OK \033[0m] \033[31m$msg\033[0m\n";
				}
			    }
			}
			if ($save)
			{
			    print SAVEF "[\033[32m $OK \033[0m] \033[31m$msg\033[0m\n";
			}
		    }
		    else
		    {
			if (is_categorie($dossier))
			{
			    ++$nbr_teste;
			    ++$nbr_failed;
			    if (!$categorie)
			    {
				if (!$final)
				{
				    print "[\033[31m $OK \033[0m] \033[31m$msg\033[0m\n";
				}
			    }
			}
			if ($save)
			{
			    print SAVEF "[\033[31m $OK \033[0m] \033[31m$msg\033[0m\n";
			}
		    }
		}
	    }
	}
    }
}

#
## This function says if the current categorie
## is in the categories list passed in argument
## of moulinette.
##
## Called by -> display.
#
sub is_categorie
{
    my $folder = shift;
    my $i = 0;

    if (!@select)
    {
	1;
    }
    else
    {
	while (($i < @select) && ($folder !~ /$select[$i]/))
	{
	    ++$i;
	}
	if ($i == @select)
	{
	    0;
	}
	else
	{
	    1;
	}
    }
}

#
## Function to display the trace passed by argument.
##
## Called by -> the script's beginning.
#
sub load
{
    my $i = 0;

    while ($i < @better)
    {
	chop $better[$i];
	if ($better[$i] =~ /\[/)
	{
	    if ($better[$i] =~ /Categorie/)
	    {
		print "$better[$i]\n\n";
	    }
	    else
	    {
		if ($better[$i] =~ /Tests reussis \[*/)
		{
		    print "\n";
		}
		print "$better[$i]\n";
		if ($better[$i] =~ /Tests reussis \[*/)
		{
		    print "\n";
		}
	    }
	}
	++$i;
    }
    exit 0;
}

#
## Beginning of script.
##
## Calls -> parcour.
## Calls -> ctimeout.
#
if (($isbetter && $save) || ($load && $save) || ($load && $isbetter))
{
    print "Checker: Invalid options association.\n";
    exit 1;
}
ctimeout;
if ($save)
{
    open(SAVEF, ">$save");
}
if ($isbetter)
{
    if (!open(LOADEF, "<$isbetter"))
    {
	print STDERR "Checker: File not found.\n";
	exit 1;
    }
    @better = <LOADEF>;
    close LOADEF;
}

if ($load)
{
    if (!open(LOADEF, "<$load"))
    {
	print STDERR "Checker: File not found.\n";
	exit 1;
    }
    @better = <LOADEF>;
    close LOADEF;
    load;
}

if ($selects)
{
    $selects =~ s/\"//;
    @select = split / / ,$selects;
}
mkdir("./rep_res", 0770);
parcour('./', '', 0);
rmdir "./rep_res";

if ($number)
{
    $nbr_failed="$nbr_failed/$nbr_teste";
    $nbr_sgresol = "$nbr_sgresol2/$nbr_segprec";
    $nbr_bi = "$nbr_bi/$nbr_teste";
    $nbr_seg = "$nbr_seg/$nbr_teste";
    $nbr_win = "$nbr_win/$nbr_teste";
}
else
{
    if ($isbetter)
    {
	if ($nbr_segprec)
	{
	    $nbr_sgresol = sprintf("%.0f", ($nbr_sgresol2 * 100) / $nbr_segprec).'%';
	}
	else
	{
	    $nbr_sgresol = "0%";
	}
    }
    $nbr_failed = sprintf("%.0f", ($nbr_failed * 100) / $nbr_teste).'%';
    $nbr_bi = sprintf("%.0f", ($nbr_bi * 100) / $nbr_teste).'%';
    $nbr_seg = sprintf("%.0f", ($nbr_seg * 100) / $nbr_teste).'%';
    $nbr_win = sprintf("%.0f", ($nbr_win * 100) / $nbr_teste).'%';
}


print "\033[35m---------------------------------------------------------------------\033[0m\n";
print " \033[31m                Tests reussis\033[0m     :=: [ \033[32m$nbr_win\033[0m ]\n";
print " \033[31m                Tests echoues\033[0m     :=: [ \033[32m$nbr_failed\033[0m ]\n";
if ($isbetter)
{
    print " \033[31m                Seg-fault resolus\033[0m :=: [ \033[32m$nbr_sgresol\033[0m ]\n";
}
print " \033[31m                Boucles infinies\033[0m  :=: [ \033[32m$nbr_bi\033[0m ]\n";
print " \033[31m                Seg-fault\033[0m         :=: [ \033[32m$nbr_seg\033[0m ]\n";
print "\033[35m---------------------------------------------------------------------\033[0m\n";

if ($save)
{
    if ($number)
    {
	$nbr_totw = "$nbr_totw/$nbr_test";
	$nbr_totf = "$nbr_totf/$nbr_test";
	$nbr_totsg = "$nbr_totsg/$nbr_test";
	$nbr_totbi = "$nbr_totbi/$nbr_test";
    }
    else
    {
	$nbr_totw = sprintf("%.0f", ($nbr_totw * 100) / $nbr_test).'%';
	$nbr_totf = sprintf("%.0f", ($nbr_totf * 100) / $nbr_test).'%';
	$nbr_totsg = sprintf("%.0f", ($nbr_totsg * 100) / $nbr_test).'%';
	$nbr_totbi = sprintf("%.0f", ($nbr_totbi * 100) / $nbr_test).'%';
    }
    print SAVEF "\033[35m---------------------------------------------------------------------\033[0m\n";
    print SAVEF " \033[31m                  Tests reussis\033[0m    :=: [ \033[32m$nbr_totw\033[0m ]\n";
    print SAVEF " \033[31m		  Tests echoues\033[0m    :=: [ \033[32m$nbr_totf\033[0m ]\n";
    print SAVEF " \033[31m		  Boucles infinies\033[0m :=: [ \033[32m$nbr_totbi\033[0m ]\n";
    print SAVEF " \033[31m		  Seg-fault\033[0m        :=: [ \033[32m$nbr_totsg\033[0m ]\n";
    print SAVEF "\033[35m---------------------------------------------------------------------\033[0m\n";
}
close SAVEF;
system("rm -rf ./*.core ./1 \- \[\]\] \] \[\]\] \\\> a ls  t rmdir mkdir rm toto trotro trutru tutu -- \]\]");
system("rmdir \[\]\]");
system(" rm \\\> ");
print "nbr_test = $nbr_teste\n";
