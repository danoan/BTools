#!/usr/bin/env bash

gp_plot_config()
{
    printf "set title '$1';
    set xlabel 'Iterations';
    set ylabel 'Integral Square Curvature (II+MDSS)';"
}

gp_add_plot()
{
    printf "'$1' u 1:5 w l title '$2',"
}

gp_last_plot()
{
	printf "'$1' u 1:5 w l title '$2';"
}