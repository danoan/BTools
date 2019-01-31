#!/bin/sh

#$1: Output filename
#$2: Graph title
#$3: Energy/Length Mode
#$4-..: (Datafile,Plot title)

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
    mode=$1;shift;

	if [ $mode = 0 ]
	then
        printf "set title '$1';
        set xlabel 'Iterations';
        set ylabel 'MDCA';"
    elif [ $mode = 1 ]
    then
        printf "set title '$1';
        set xlabel 'Iterations';
        set ylabel 'MDCA/Perimeter';"
    elif [ $mode = 2 ]
    then
        printf "set title '$1';
        set xlabel 'Iterations';
        set ylabel 'Unlabeled';"
    fi
}


gp_add_plot()
{
    mode=$1;shift;

    if [ $mode = 0 ]
    then
	    printf "'$1' u 1:3 w l title '$2',"
	elif [ $mode = 1 ]
	then
	    printf "'$1' u 1:(\$3/\$4) w l title '$2',"
    elif [ $mode = 2 ]
    then
    	printf "'$1' u 1:5 w l title '$2',"
	fi

}

gp_last_plot()
{
    mode=$1;shift;

    if [ $mode = 0 ]
    then
	    printf "'$1' u 1:3 w l title '$2';"
	elif [ $mode = 1 ]
	then
	    printf "'$1' u 1:(\$3/\$4) w l title '$2';"
	elif [ $mode = 2 ]
	then
	    printf "'$1' u 1:5 w l title '$2';"
	fi
}


run()
{
	fileoutput=$1;shift;
	graphtitle=$1;shift;
	mode=$1;shift;

	buffer="$(gp_plot_config $mode $graphtitle)plot "
	i=0
	num_plots=`expr ${#} / 2 - 1`
	while [ ${i} -lt ${num_plots} ]
	do
		filepath=$1
		title=$2
		buffer="${buffer}$(gp_add_plot $mode $filepath $title)"
		shift; shift;

		i=`expr $i + 1`
	done
	
	if [ $num_plots -eq 0 ]
	then
		buffer="${buffer}$(gp_last_plot $mode $1 $2)"
	else	
		buffer="${buffer}$(gp_last_plot $mode $1 $2)"
	fi

	buffer="${buffer}$(gp_save)"

	`gnuplot -e "$buffer"`
	`mv my-plot.ps ${fileoutput}`
}


run $@
