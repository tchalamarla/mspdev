//******************************************************************************
//  MSP430F20xx Demo - P1 Interrupt from LPM4 with Internal Pull-up
//
//  Description: A hi/low transition on P1.4 will trigger P1_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA.
//  Internal pullup enabled on P1.4.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F20xx
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |      R          |
//      --o--| P1.4-o      P1.0|-->LED
//     \|/
//
//  M. Buccini / L. Westlund
//  Texas Instruments Inc.
//  November 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40A
//******************************************************************************

#include  <msp430x20x3.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0x01;                             // P1.0 output, else input
  P1OUT =  0x10;                            // P1.4 set, else reset
  P1REN |= 0x10;                            // P1.4 pullup
  P1IE |= 0x10;                             // P1.4 interrupt enabled
  P1IES |= 0x10;                            // P1.4 Hi/lo edge
  P1IFG &= ~0x10;                           // P1.4 IFG cleared

  _BIS_SR(LPM4_bits + GIE);                 // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= 0x01;                            // P1.0 = toggle
  P1IFG &= ~0x10;                           // P1.4 IFG cleared
}

