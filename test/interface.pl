#!/usr/bin/perl -w
## exo2.pl for  in /u/a1/raymon_e
##
## Made by enguerrand raymond
## Login   <raymon_e@epita.fr>
##
## Started on  Tue Jan  4 21:01:39 2005 enguerrand raymond
## Last update Tue Jan 11 13:57:47 2005 enguerrand raymond
##

use strict;
use Tk;

#
## Main widget, main window.
#
my $main=MainWindow->new(-title => 'Moulinette 42sh', -height => '150', -width => '400');

#
## Frame to place the widgets.
#
my $frame=$main->Frame(-height => '50', -width => '10');
$frame->pack(-side => 'left');

#
## Buttons for the moulinette options.
#
my $but0=$frame->Button(-background => "white", -text => 'Normal',
		       -command => [\&moulinette,"./"])->pack;
my $but1=$frame->Button(-background => "red", -text => 'Categories',
		       -command => [\&start,"./"])->pack;
my $but2=$frame->Button(-background => "green", -text => 'Is better',
		       -command => [\&start,"./"])->pack;
my $but3=$frame->Button(-background => "blue", -text => 'Number',
		       -command => [\&start,"./"])->pack;
my $but4=$frame->Button(-background => "red", -text => 'Select',
		       -command => [\&start,"./"])->pack;
my $but5=$frame->Button(-background => "green", -text => 'Save',
		       -command => [\&start,"./"])->pack;
my $but6=$frame->Button(-background => "blue", -text => 'Load',
		       -command => [\&start,"./"])->pack;
my $but7=$frame->Button(-background => "red", -text => 'Final',
		       -command => [\&start,"./"])->pack;
my $but8=$frame->Button(-background => "green", -text => 'All',
		       -command => [\&start,"./"])->pack;
my $but9=$frame->Button(-background => "black", -text => 'Quit',
		       -command => [\&quit,"./"])->pack;

#
## Widget to display the results of the moulinette.
#
my $list_res=$main->Scrolled('Listbox', -scrollbars => 'oe');

#
## Widget scrollbar.
#
#my $scroll=$main->Scrollbar(-command => ['yview', $list_res]);
#$list_res->configure(-yscrollcommand => ['set', $scroll]);
#$scroll->pack(-side => 'right', -fill => 'y');

#
## Buttons size.
#
$but0->configure(-width => '10');
$but1->configure(-width => '10');
$but2->configure(-width => '10');
$but3->configure(-width => '10');
$but4->configure(-width => '10');
$but5->configure(-width => '10');
$but6->configure(-width => '10');
$but7->configure(-width => '10');
$but8->configure(-width => '10');
$but9->configure(-width => '10');

#
## List box size.
#
$list_res->configure(-height => '35', -width => '60');
$list_res->pack(-side => 'left', -expand => 'y', -fill => 'both');

sub moulinette
{
    my @tab;
    my $i;

    system "./checker.pl > res";
    #system("./checker.pl");
    open(RES, "<./res");
    @tab=<RES>;
    #$list_res->insert('end', "efef");
    for ($i=0; $i < @tab; ++$i)
    {
	chop $tab[$i];
	$tab[$i] =~ s/\033\[31m//g;
	$tab[$i] =~ s/\033\[32m//g;
	$tab[$i] =~ s/\033\[33m//g;
	$tab[$i] =~ s/\033\[36m//g;
	$tab[$i] =~ s/\033\[35m//g;
	$tab[$i] =~ s/\033\[0m//g;
	$tab[$i] =~ s/\\n//g;
	$tab[$i] =~ s/\[ OK \]//g;
	$tab[$i] =~ s/\[ KO \]//g;
	$tab[$i] =~ s/\[ SG \]//g;
	$tab[$i] =~ s/\[ TO \]//g;
	$list_res->insert('end', $tab[$i]);
	$main->update;
    }
    close(RES);
}

sub quit
{
    exit 0;
}

MainLoop;
