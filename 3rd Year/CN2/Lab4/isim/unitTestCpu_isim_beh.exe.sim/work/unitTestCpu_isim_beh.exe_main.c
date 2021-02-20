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
    work_m_00000000000368230782_0266380040_init();
    work_m_00000000000752829291_0782664348_init();
    work_m_00000000000569508273_1262452598_init();
    work_m_00000000003359680628_3648169201_init();
    work_m_00000000002464410394_3052468000_init();
    work_m_00000000001379507881_0052631370_init();
    work_m_00000000000593596388_1696645267_init();
    work_m_00000000002656834208_3356059340_init();
    work_m_00000000000173021144_1835084805_init();
    work_m_00000000000260405604_1200043877_init();
    work_m_00000000002206718090_2524751178_init();
    work_m_00000000000025683111_0329307366_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000000025683111_0329307366");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
