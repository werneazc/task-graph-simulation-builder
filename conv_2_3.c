struct inPixels_4_4
{
	int iPix_0_1;
	int iPix_1_2;
	int iPix_m1_1;
	int iPix_0_0;
	int iPix_m1_0;
	int iPix_2_m1;
	int iPix_2_2;
	int iPix_2_1;
	int iPix_0_2;
	int iPix_2_0;
	int iPix_m1_2;
	int iPix_m1_m1;
	int iPix_0_m1;
	int iPix_1_0;
	int iPix_1_m1;
	int iPix_1_1;
};

struct maskPixels_3_3
{
	int k_0_1;
	int k_m1_1;
	int k_0_0;
	int k_m1_0;
	int k_m1_m1;
	int k_0_m1;
	int k_1_0;
	int k_1_m1;
	int k_1_1;
};

struct outPixels_2_2
{
	int oPix_0_1;
	int oPix_1_0;
	int oPix_0_0;
	int oPix_1_1;
};



struct outPixels_2_2 conv_2_3( struct inPixels_4_4 inputPixels, struct maskPixels_3_3 weights )
{
	struct outPixels_2_2 outputPixels;

	outputPixels.oPix_0_1 = inputPixels.iPix_0_2 * weights.k_0_1 + inputPixels.iPix_1_2 * weights.k_1_1 ;
	outputPixels.oPix_0_1 += inputPixels.iPix_m1_2 * weights.k_m1_1 ;
	outputPixels.oPix_0_1 += inputPixels.iPix_0_1 * weights.k_0_0 + inputPixels.iPix_0_0 * weights.k_0_m1 + inputPixels.iPix_1_1 * weights.k_1_0 + inputPixels.iPix_1_0 * weights.k_1_m1 ;
	outputPixels.oPix_0_1 += inputPixels.iPix_m1_1 * weights.k_m1_0 + inputPixels.iPix_m1_0 * weights.k_m1_m1 ;

	outputPixels.oPix_1_0 = inputPixels.iPix_0_m1 * weights.k_m1_m1 + inputPixels.iPix_1_m1 * weights.k_0_m1 ;
	outputPixels.oPix_1_0 += inputPixels.iPix_2_0 * weights.k_1_0 + inputPixels.iPix_2_1 * weights.k_1_1 ;
	outputPixels.oPix_1_0 += inputPixels.iPix_1_1 * weights.k_0_1 + inputPixels.iPix_0_1 * weights.k_m1_1 + inputPixels.iPix_1_0 * weights.k_0_0 + inputPixels.iPix_0_0 * weights.k_m1_0 ;
	outputPixels.oPix_1_0 += inputPixels.iPix_2_m1 * weights.k_1_m1 ;

	outputPixels.oPix_0_0 = inputPixels.iPix_0_m1 * weights.k_0_m1 + inputPixels.iPix_1_m1 * weights.k_1_m1 ;
	outputPixels.oPix_0_0 += inputPixels.iPix_0_1 * weights.k_0_1 + inputPixels.iPix_0_0 * weights.k_0_0 + inputPixels.iPix_1_0 * weights.k_1_0 + inputPixels.iPix_1_1 * weights.k_1_1 ;
	outputPixels.oPix_0_0 += inputPixels.iPix_m1_1 * weights.k_m1_1 + inputPixels.iPix_m1_0 * weights.k_m1_0 ;
	outputPixels.oPix_0_0 += inputPixels.iPix_m1_m1 * weights.k_m1_m1 ;

	outputPixels.oPix_1_1 = inputPixels.iPix_1_2 * weights.k_0_1 + inputPixels.iPix_0_2 * weights.k_m1_1 ;
	outputPixels.oPix_1_1 += inputPixels.iPix_2_1 * weights.k_1_0 + inputPixels.iPix_2_0 * weights.k_1_m1 ;
	outputPixels.oPix_1_1 += inputPixels.iPix_1_1 * weights.k_0_0 + inputPixels.iPix_0_1 * weights.k_m1_0 + inputPixels.iPix_0_0 * weights.k_m1_m1 + inputPixels.iPix_1_0 * weights.k_0_m1 ;
	outputPixels.oPix_1_1 += inputPixels.iPix_2_2 * weights.k_1_1 ;

	 return outputPixels;
}