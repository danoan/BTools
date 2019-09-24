#!/usr/bin/env bash

gp_plot_config()
{
    mode=$1;shift;

    printf "set title '$1';
    set xlabel 'Iterations';
    set ylabel 'Shape perimeter';"
}

gp_add_plot()
{
    printf "'$1' u 1:4 w l title '$2',"
}

gp_last_plot()
{
	printf "'$1' u 1:4 w l title '$2';"
}