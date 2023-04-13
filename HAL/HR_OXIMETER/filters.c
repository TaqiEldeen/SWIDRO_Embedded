/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 20 Feb 2023		 **************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "filters.h"




/* ********************************************************************* */
/* ************************** DC Removal Filter ************************ */
/* ********************************************************************* */
DC_Filter HR_OXIMETER_DCRemoval(f32 A_FuncX, f32 A_PrevW, f32 alpha)
{
    // IIR Filter
	// prev + w(sample - prev)
	// value  + (alpha - 1)prev
    DC_Filter filtered;
    filtered.w = A_FuncX + (alpha * A_PrevW);
    filtered.result = filtered.w - A_PrevW;
    return filtered;
}

/* ********************************************************************* */
/* ************************** Mean Median Filter************************ */
/* ********************************************************************* */
f32 HR_OXIMETER_f32MeanDiff(f32 A_f32Input, MEANDiff_Filter *A_FilterValues)
{
    f32 avg = 0;

    A_FilterValues->sum -= A_FilterValues->values[A_FilterValues->index];
    A_FilterValues->values[A_FilterValues->index] = A_f32Input;
    A_FilterValues->sum += A_FilterValues->values[A_FilterValues->index];

    A_FilterValues->index++;
    A_FilterValues->index = A_FilterValues->index % MEAN_FILTER_SIZE;

    if (A_FilterValues->count < MEAN_FILTER_SIZE)
        A_FilterValues->count++;

    avg = A_FilterValues->sum / A_FilterValues->count;
    return ( A_f32Input - avg );
}


//f32 HR_OXIMETER_f32MeanDiff_2(f32 A_f32Input, MEANDiff_Filter *A_FilterValues)
//{
//    f32 avg = 0;
//
//    // Initialize index if necessary
//    if (A_FilterValues->count == 0) {
//        A_FilterValues->index = 0;
//    }
//
//    // Subtract oldest value from sum
//    A_FilterValues->sum -= A_FilterValues->values[A_FilterValues->index];
//
//    // Add new value to buffer and update sum
//    A_FilterValues->values[A_FilterValues->index] = A_f32Input;
//    A_FilterValues->sum += A_f32Input;
//
//    // Update index and count
//    A_FilterValues->index++;
//    A_FilterValues->index = A_FilterValues->index % MEAN_FILTER_SIZE;
//    A_FilterValues->count = min(A_FilterValues->count + 1, MEAN_FILTER_SIZE);
//
//    // Calculate average and return difference
//    avg = A_FilterValues->sum / (f32)A_FilterValues->count;
//    return (A_f32Input - avg);
//}


/* ********************************************************************* */
/* ************************** Butterworth filter  ************************ */
/* ********************************************************************* */
void HR_OXIMETER_vLowPassButterworthFilter(f32 A_f32Input, Butterworth_Filter *A_filterResult)
{
    A_filterResult->values[0] = A_filterResult->values[1];

    // Fs = 100Hz and Fc = 10Hz
    A_filterResult->values[1] = (2.452372752527856026e-1 * A_f32Input) + (0.50952544949442879485 * A_filterResult->values[0]);

    // Fs = 100Hz and Fc = 4Hz
    //= A_filterResult->values[1] = (1.367287359973195227e-1 * A_f32Input) + (0.72654252800536101020 * A_filterResult->values[0]); //valuesery precise butterworth filter

    A_filterResult->result = A_filterResult->values[0] + A_filterResult->values[1];
}
