/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 20 Feb 2023		 	**************/
/*********************************************************/

#ifndef HAL_HR_OXIMETER_FILTERS_H_
#define HAL_HR_OXIMETER_FILTERS_H_

#define MEAN_FILTER_SIZE 20 	/* 20 */
#define MEAN_FILTER_SIZE_2 100

typedef struct
{
    f32 w;
    f32 result;
} DC_Filter;


typedef struct
{
    f32 values[MEAN_FILTER_SIZE];
    u8 index;
    f32 sum;
    u8 count;
} MEANDiff_Filter;

typedef struct {
    f32 values[MEAN_FILTER_SIZE];
    f32 sum;
    u32 index;
    u32 count;
} MEANDiff_Filter_2;


typedef struct
{
    f32 values[2];
    f32 result;
} Butterworth_Filter;


DC_Filter HR_OXIMETER_DCRemoval(f32 A_FuncX, f32 A_PrevW, f32 alpha);

f32 HR_OXIMETER_f32MeanDiff(f32 A_f32Input, MEANDiff_Filter *A_FilterValues);

void HR_OXIMETER_vLowPassButterworthFilter(f32 A_f32Input, Butterworth_Filter *A_filterResult);


#endif /* HAL_HR_OXIMETER_FILTERS_H_ */
