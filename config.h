#ifndef CONFIG_H
#define CONFIG_H

// IMPORTANT
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ETSI_EUROPE_REGULATION 1
#define FCC_US_REGULATION 2
#define SENEGAL_REGULATION 3

/* Set this to the right regulation from above */
#define LORA_REGULATION FCC_US_REGULATION
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// IMPORTANT
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// uncomment if your radio is an HopeRF RFM92W, HopeRF RFM95W, Modtronix inAir9B, NiceRF1276
// or you known from the circuit diagram that output use the PABOOST line instead of the RFO line
//#define PABOOST
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// IMPORTANT
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BAND868 1
#define BAND900 2
#define BAND433 3

/* Set this to the right band from above */
#define LORA_BAND BAND868
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* Guard */
