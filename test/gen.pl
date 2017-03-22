#!/usr/bin/perl -w
## gen.pl for 42sh in /u/a1/delest_o/grosli_o-42sh/test
##
## Made by olivier delestre
## Login   <delest_o@epita.fr>
##
## Started on  Tue Jan  4 22:07:43 2005 olivier delestre
## Last update Thu Jan  6 20:42:39 2005 enguerrand raymond
##


use strict;

sub ask
{
    my $path;
    my $var;
    my @tab;

    print "1. Entrer le chemin du fichier a creer\n";
    $path = <STDIN>;
    chop $path;
    open(FILE, ">>$path");
    print "1,5. Entrer l'id du test\n";
    $var = <STDIN>;
    print FILE "#$var";
    print "2. Entrer le descriptif associe au test cree\n";
    $var = <STDIN>;
    print FILE "#$var";
    print FILE "\n";
    print "3. Entrer le test cree\n";
    while ($var = <STDIN>)
    {
	print FILE $var;
    }
    print "4. Ajout au repository CVS\n";
    @tab =("cvs", "add", $path);
    system @tab;
    print "5. Commit du CVS\n";
    @tab =("cvs", "commit");
    system @tab;
    print "6. Test cree\n";
}

ask()
