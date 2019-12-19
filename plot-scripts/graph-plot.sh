#!/usr/bin/env bash

gp_save()
{
    pi=10
    printf "set style line 1 lc rgb '#bf3a2c' pt 1 ps 2 lt 1 lw 2 pi $pi;
            set style line 2 lc rgb '#577bb4' pt 2 ps 2 lt 1 lw 2 pi $pi;
            set style line 3 lc rgb '#77ac50' pt 3 ps 2 lt 1 lw 2 pi $pi;
            set style line 4 lc rgb '#8551a0' pt 4 ps 1 lt 1 lw 2 pi $pi;
            set style line 5 lc rgb '#df8528' pt 5 ps 1 lt 1 lw 2 pi $pi;
            set style line 6 lc rgb '#fdfd4a' pt 6 ps 1 lt 1 lw 2 pi $pi;
	        set style line 7 lc rgb '#915b32' pt 7 ps 1 lt 1 lw 2 pi $pi;
            set style line 8 lc rgb '#d9885be' pt 8 ps 1 lt 1 lw 2 pi $pi;
            set style line 9 lc rgb '#989898' pt 9 ps 1 lt 1 lw 2 pi $pi;"

    printf "set style line 11 lc rgb '#808080' lt 1;
            set border 3 back ls 11;
            set tics nomirror;"

    printf "set style line 12 lc rgb '#808080' lt 0 lw 1;
            set grid back ls 12;"

    printf "set size 1.0, 0.6;
            set terminal postscript portrait enhanced color lw 2 \"Helvetica\" 20;
            set key right center;
            set output \"my-plot.ps\";
            replot;
            set terminal x11;
            set size 1,1;"
}

gp_add_plot()
{
    printf "'$1' u 1:2 w lp ls $3 title '$2',"
}

gp_last_plot()
{
	printf "'$1' u 1:2 w lp ls $3 title '$2';"
}


create_multiplot()
{
	fileoutput=$1;shift;
	plottitle="$1";shift;

	buffer="$(gp_plot_config "$plottitle")plot "
	i=0
	num_plots=`expr ${#} / 2 - 1`

	while [ ${i} -lt ${num_plots} ]
	do
	    i=`expr $i + 1`

		subplotDataFile=$1
		subplotTitle=$2
		buffer="${buffer}$(gp_add_plot $subplotDataFile $subplotTitle $i)"
		shift; shift;
	done

	i=`expr $i + 1`

	if [ $num_plots -eq 0 ]
	then
		buffer="${buffer}$(gp_last_plot $1 $2 $i)"
	else
		buffer="${buffer}$(gp_last_plot $1 $2 $i)"
	fi

	buffer="${buffer}$(gp_save)"


	`gnuplot -e "$buffer"`
	`mv my-plot.ps ${fileoutput}`
}