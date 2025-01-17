/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000002204324536_0457016286_init();
    work_m_00000000000345341303_0266380040_init();
    work_m_00000000000752829291_0782664348_init();
    work_m_00000000002316671827_1262452598_init();
    work_m_00000000001393280709_1351276808_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000001393280709_1351276808");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
