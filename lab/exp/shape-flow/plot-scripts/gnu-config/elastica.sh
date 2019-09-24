#!/usr/bin/env bash

gp_plot_config()
{
    mode=$1;shift;

    printf "set title '$1';
    set xlabel 'Iterations';
    set ylabel 'Integral Square Curvature (MDCA+MDSS)';"
}

gp_add_plot()
{
    printf "'$1' u 1:3 w l title '$2',"
}

gp_last_plot()
{
	printf "'$1' u 1:3 w l title '$2';"
}