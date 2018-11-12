#!/bin/sh

gp_save()
{
	printf "set size 1.0, 0.6;
		set terminal postscript portrait enhanced color dashed lw 1 \"Helvetica\" 14;
		set output \"my-plot.ps\";
		replot;
		set terminal x11;
		set size 1,1;"
}

gp_plot_config()
{
	printf "set title '$1';
		set xlabel 'Iterations';
		set ylabel 'MDCA';" 
}


gp_add_plot()
{
	printf "'$1' u 1:4 w l title '$2',"
}

gp_last_plot()
{
	printf "'$1' u 1:4 w l title '$2';"
}


run()
{
	fileoutput=$1;shift;
	graphtitle=$1;shift;

	buffer="$(gp_plot_config $graphtitle)plot "
	i=0
	num_plots=`expr ${#} / 2 - 1`
	while [ ${i} -lt ${num_plots} ]
	do
		filepath=$1
		title=$2
		buffer="${buffer}$(gp_add_plot $filepath $title)"  
		shift; shift;

		i=`expr $i + 1`
	done
	
	if [ $num_plots -eq 0 ]
	then
		buffer="${buffer}$(gp_last_plot $1 $2)"
	else	
		buffer="${buffer}$(gp_last_plot $1 $2)"
	fi

	buffer="${buffer}$(gp_save)"

	`gnuplot -e "$buffer"`
	`mv my-plot.ps ${fileoutput}`
}


run $@
