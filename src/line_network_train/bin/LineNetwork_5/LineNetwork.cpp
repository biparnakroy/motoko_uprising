#include "LineNetwork.h"

#include "layer_0.h"
#include "layer_1.h"
#include "layer_2.h"
#include "layer_3.h"
#include "layer_4.h"
#include "layer_5.h"
#include "layer_6.h"


LineNetwork::LineNetwork()
			:NeuralNetwork()
{
		input_geometry.w = 8;
		input_geometry.h = 8;
		input_geometry.d = 1;

		output_geometry.w = 1;
		output_geometry.h = 1;
		output_geometry.d = 8;

		layers[0] = new NetDenseConvolutionLayer(layer_0_kernel_geometry,layer_0_input_geometry,layer_0_output_geometry,layer_0_weights,layer_0_bias,layer_0_weights_range,layer_0_bias_range);
		layers[1] = new NetReluLayer(layer_1_kernel_geometry,layer_1_input_geometry,layer_1_output_geometry);
		layers[2] = new NetDenseConvolutionLayer(layer_2_kernel_geometry,layer_2_input_geometry,layer_2_output_geometry,layer_2_weights,layer_2_bias,layer_2_weights_range,layer_2_bias_range);
		layers[3] = new NetReluLayer(layer_3_kernel_geometry,layer_3_input_geometry,layer_3_output_geometry);
		layers[4] = new NetDenseConvolutionLayer(layer_4_kernel_geometry,layer_4_input_geometry,layer_4_output_geometry,layer_4_weights,layer_4_bias,layer_4_weights_range,layer_4_bias_range);
		layers[5] = new NetReluLayer(layer_5_kernel_geometry,layer_5_input_geometry,layer_5_output_geometry);
		layers[6] = new NetFcLayer(layer_6_kernel_geometry,layer_6_input_geometry,layer_6_output_geometry,layer_6_weights,layer_6_bias,layer_6_weights_range,layer_6_bias_range);

		layers_count = 7;
		allocate_buffer();
}


LineNetwork::~LineNetwork()
{
		for (unsigned int i = 0; i < layers_count; i++)
		{
			delete layers[i];
			layers[i] = nullptr;
		}
}