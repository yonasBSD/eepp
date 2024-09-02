#include <eepp/ui/doc/languages/glsl.hpp>
#include <eepp/ui/doc/syntaxdefinitionmanager.hpp>

namespace EE { namespace UI { namespace Doc { namespace Language {

void addGLSL() {

	auto& sd = SyntaxDefinitionManager::instance()->add(

		{ "GLSL",
		  { "%.glsl$", "%.frag$", "%.vert$", "%.fs$", "%.vs$", "%.tesc", "%.tese" },
		  {
			  { { "//.-\n" }, "comment" },
			  { { "/%*", "%*/" }, "comment" },
			  { { "#", "\n" }, "comment" },
			  { { "\"", "\"", "\\" }, "string" },
			  { { "'", "'", "\\" }, "string" },
			  { { "-?0x%x+" }, "number" },
			  { { "-?%d+[%d%.eE]*f?" }, "number" },
			  { { "-?%.?%d+f?" }, "number" },
			  { { "[%+%-=/%*%^%%<>!~|&]" }, "operator" },
			  { { "ivec[2-4]" }, "keyword2" },
			  { { "bvec[2-4]" }, "keyword2" },
			  { { "uvec[2-4]" }, "keyword2" },
			  { { "vec[2-4]" }, "keyword2" },
			  { { "dmat[2-4]x[2-4]" }, "keyword2" },
			  { { "dmat[2-4]" }, "keyword2" },
			  { { "mat[2-4]x[2-4]" }, "keyword2" },
			  { { "mat[2-4]" }, "keyword2" },
			  { { "[%a_][%w_]*%f[(]" }, "function" },
			  { { "[%a_][%w_]*" }, "symbol" },

		  },
		  {
			  { "atomicExchange", "keyword" },
			  { "atomicXor", "keyword" },
			  { "imageAtomicMax", "keyword" },
			  { "atomicAnd", "keyword" },
			  { "step", "keyword" },
			  { "uimage2DArray", "keyword2" },
			  { "atomicMax", "keyword" },
			  { "atomicCounterCompSwap", "keyword" },
			  { "atomicCounterExchange", "keyword" },
			  { "atomicCounterXor", "keyword" },
			  { "atomicMin", "keyword" },
			  { "atomicCounterMax", "keyword" },
			  { "utexture2DMSArray", "keyword" },
			  { "atomicCounterMin", "keyword" },
			  { "atomicCounterSubtract", "keyword" },
			  { "textureProjGradOffset", "keyword" },
			  { "textureGather", "keyword" },
			  { "utextureBuffer", "keyword" },
			  { "textureProjGrad", "keyword" },
			  { "textureGrad", "keyword" },
			  { "sampler2DMS", "keyword2" },
			  { "textureProjLodOffset", "keyword" },
			  { "textureProjLod", "keyword" },
			  { "textureLodOffset", "keyword" },
			  { "dFdy", "keyword" },
			  { "textureOffset", "keyword" },
			  { "textureProj", "keyword" },
			  { "uaddCarry", "keyword" },
			  { "patch", "keyword" },
			  { "textureLod", "keyword" },
			  { "imageSize", "keyword" },
			  { "texture", "keyword" },
			  { "sample", "keyword" },
			  { "textureQueryLod", "keyword" },
			  { "bitCount", "keyword" },
			  { "bitfieldExtract", "keyword" },
			  { "umulExtended", "keyword" },
			  { "memoryBarrierImage", "keyword" },
			  { "usubBorrow", "keyword" },
			  { "atomicCounterAdd", "keyword" },
			  { "interpolateAtOffset", "keyword" },
			  { "not", "keyword" },
			  { "bitfieldReverse", "keyword" },
			  { "textureGatherOffset", "keyword" },
			  { "equal", "keyword" },
			  { "greaterThanEqual", "keyword" },
			  { "greaterThan", "keyword" },
			  { "lessThanEqual", "keyword" },
			  { "isampler1D", "keyword2" },
			  { "atomicCompSwap", "keyword" },
			  { "lessThan", "keyword" },
			  { "determinant", "keyword" },
			  { "imageAtomicAdd", "keyword" },
			  { "isampler1DArray", "keyword2" },
			  { "matrixCompMult", "keyword" },
			  { "floatBitsToInt", "keyword" },
			  { "refract", "keyword" },
			  { "imageAtomicMin", "keyword" },
			  { "faceforward", "keyword" },
			  { "ftransform", "keyword" },
			  { "sqrt", "keyword" },
			  { "cross", "keyword" },
			  { "abs", "keyword" },
			  { "packDouble2x32", "keyword" },
			  { "unpackSnorm4x8", "keyword" },
			  { "utexture1DArray", "keyword" },
			  { "unpackUnorm4x8", "keyword" },
			  { "texture1DArray", "keyword" },
			  { "packUnorm2x16", "keyword" },
			  { "frexp", "keyword" },
			  { "fma", "keyword" },
			  { "isnan", "keyword" },
			  { "mix", "keyword" },
			  { "exp2", "keyword" },
			  { "isampler3D", "keyword2" },
			  { "false", "literal" },
			  { "sampler2DMSArray", "keyword2" },
			  { "packHalf2x16", "keyword" },
			  { "sampler2DArrayShadow", "keyword2" },
			  { "lowp", "keyword" },
			  { "length", "keyword" },
			  { "imageLoad", "keyword" },
			  { "imulExtended", "keyword" },
			  { "smooth", "keyword" },
			  { "sampler1DShadow", "keyword2" },
			  { "utexture2DArray", "keyword" },
			  { "isampler2D", "keyword2" },
			  { "iimage1D", "keyword2" },
			  { "uimageCubeArray", "keyword2" },
			  { "memoryBarrierAtomicCounter", "keyword" },
			  { "utexture2DMS", "keyword" },
			  { "tanh", "keyword" },
			  { "atomicCounterAnd", "keyword" },
			  { "invariant", "keyword" },
			  { "layout", "keyword" },
			  { "imageStore", "keyword" },
			  { "sampler2DRectShadow", "keyword2" },
			  { "fwidth", "keyword" },
			  { "volatile", "keyword" },
			  { "imageBuffer", "keyword2" },
			  { "usampler1DArray", "keyword2" },
			  { "usampler2DArray", "keyword2" },
			  { "utextureCubeArray", "keyword" },
			  { "findLSB", "keyword" },
			  { "texelFetch", "keyword" },
			  { "dot", "keyword" },
			  { "atomicOr", "keyword" },
			  { "isinf", "keyword" },
			  { "imageCube", "keyword2" },
			  { "true", "literal" },
			  { "texture1D", "keyword" },
			  { "inverse", "keyword" },
			  { "dFdyFine", "keyword" },
			  { "memoryBarrierShared", "keyword" },
			  { "atomicCounterOr", "keyword" },
			  { "usampler1D", "keyword2" },
			  { "uniform", "keyword" },
			  { "image1DArray", "keyword2" },
			  { "writeonly", "keyword" },
			  { "itexture2DRect", "keyword" },
			  { "precision", "keyword" },
			  { "imageSamples", "keyword" },
			  { "isampler2DMSArray", "keyword2" },
			  { "dFdx", "keyword" },
			  { "image1D", "keyword2" },
			  { "atomicCounterIncrement", "keyword" },
			  { "image2D", "keyword2" },
			  { "image2DArray", "keyword2" },
			  { "any", "keyword" },
			  { "uimageCube", "keyword2" },
			  { "iimage2DArray", "keyword2" },
			  { "memoryBarrierBuffer", "keyword" },
			  { "allInvocationsEqual", "keyword" },
			  { "sampler3D", "keyword2" },
			  { "subpassLoad", "keyword" },
			  { "itexture2D", "keyword" },
			  { "image2DMS", "keyword2" },
			  { "itexture1DArray", "keyword" },
			  { "centroid", "keyword" },
			  { "dFdyCoarse", "keyword" },
			  { "texture2DArray", "keyword" },
			  { "iimage2DRect", "keyword2" },
			  { "utexture2D", "keyword" },
			  { "texture3D", "keyword" },
			  { "itextureCube", "keyword" },
			  { "degrees", "keyword" },
			  { "texture2DMS", "keyword" },
			  { "itexture2DMS", "keyword" },
			  { "iimage2DMS", "keyword2" },
			  { "isubpassInput", "keyword2" },
			  { "imageAtomicXor", "keyword" },
			  { "samplerShadow", "keyword2" },
			  { "iimage2D", "keyword2" },
			  { "usampler3D", "keyword2" },
			  { "itexture2DMSArray", "keyword" },
			  { "sin", "keyword" },
			  { "utexture2DRect", "keyword" },
			  { "do", "keyword" },
			  { "groupMemoryBarrier", "keyword" },
			  { "image3D", "keyword2" },
			  { "usubpassInput", "keyword2" },
			  { "isampler2DMS", "keyword2" },
			  { "samplerBuffer", "keyword2" },
			  { "texture2DRect", "keyword" },
			  { "while", "keyword" },
			  { "memoryBarrier", "keyword" },
			  { "samplerCubeArrayShadow", "keyword2" },
			  { "outerProduct", "keyword" },
			  { "interpolateAtCentroid", "keyword" },
			  { "subpassInput", "keyword2" },
			  { "noperspective", "keyword" },
			  { "textureBuffer", "keyword" },
			  { "EmitVertex", "keyword" },
			  { "usubpassInputMS", "keyword2" },
			  { "iimageCubeArray", "keyword2" },
			  { "interpolateAtSample", "keyword" },
			  { "const", "keyword" },
			  { "uimage2DMSArray", "keyword2" },
			  { "uimage1D", "keyword2" },
			  { "texture2D", "keyword" },
			  { "subpassInputMS", "keyword2" },
			  { "textureGatherOffsets", "keyword" },
			  { "EmitStreamVertex", "keyword" },
			  { "precise", "keyword" },
			  { "uimage2DRect", "keyword2" },
			  { "textureCube", "keyword" },
			  { "uimage2DMS", "keyword2" },
			  { "EndPrimitive", "keyword" },
			  { "utexture3D", "keyword" },
			  { "utextureCube", "keyword" },
			  { "fwidthCoarse", "keyword" },
			  { "varying", "keyword" },
			  { "itexture1D", "keyword" },
			  { "dFdxCoarse", "keyword" },
			  { "imageCubeArray", "keyword2" },
			  { "image2DMSArray", "keyword2" },
			  { "dFdxFine", "keyword" },
			  { "EndStreamPrimitive", "keyword" },
			  { "imageAtomicExchange", "keyword" },
			  { "imageAtomicAnd", "keyword" },
			  { "imageAtomicOr", "keyword" },
			  { "allInvocations", "keyword" },
			  { "imageAtomicCompSwap", "keyword" },
			  { "highp", "keyword" },
			  { "fwidthFine", "keyword" },
			  { "cos", "keyword" },
			  { "texture2DMSArray", "keyword" },
			  { "radians", "keyword" },
			  { "itexture3D", "keyword" },
			  { "modf", "keyword" },
			  { "unpackDouble2x32", "keyword" },
			  { "usampler2DMSArray", "keyword2" },
			  { "acos", "keyword" },
			  { "smoothstep", "keyword" },
			  { "atomicCounterDecrement", "keyword" },
			  { "iimageCube", "keyword2" },
			  { "uimage3D", "keyword2" },
			  { "samplerCube", "keyword2" },
			  { "mod", "keyword" },
			  { "clamp", "keyword" },
			  { "isubpassInputMS", "keyword2" },
			  { "textureGradOffset", "keyword" },
			  { "asin", "keyword" },
			  { "attribute", "keyword" },
			  { "sampler2DArray", "keyword2" },
			  { "image2DRect", "keyword2" },
			  { "notEqual", "keyword" },
			  { "log2", "keyword" },
			  { "readonly", "keyword" },
			  { "uimageBuffer", "keyword2" },
			  { "floatBitsToUint", "keyword" },
			  { "itextureBuffer", "keyword" },
			  { "iimage3D", "keyword2" },
			  { "packUnorm4x8", "keyword" },
			  { "inout", "keyword" },
			  { "return", "keyword" },
			  { "uimage1DArray", "keyword2" },
			  { "min", "keyword" },
			  { "samplerCubeArray", "keyword2" },
			  { "texelFetchOffset", "keyword" },
			  { "sampler", "keyword2" },
			  { "float", "keyword2" },
			  { "uintBitsToFloat", "keyword" },
			  { "int", "keyword2" },
			  { "mediump", "keyword" },
			  { "subroutine", "keyword" },
			  { "distance", "keyword" },
			  { "reflect", "keyword" },
			  { "usampler2D", "keyword2" },
			  { "all", "keyword" },
			  { "intBitsToFloat", "keyword" },
			  { "out", "keyword" },
			  { "double", "keyword2" },
			  { "usamplerBuffer", "keyword2" },
			  { "atomicCounter", "keyword" },
			  { "if", "keyword" },
			  { "tan", "keyword" },
			  { "continue", "keyword" },
			  { "in", "keyword" },
			  { "atan", "keyword" },
			  { "else", "keyword" },
			  { "switch", "keyword" },
			  { "bool", "keyword2" },
			  { "anyInvocation", "keyword" },
			  { "usampler2DRect", "keyword2" },
			  { "packSnorm2x16", "keyword" },
			  { "textureProjOffset", "keyword" },
			  { "usamplerCube", "keyword2" },
			  { "atomicAdd", "keyword" },
			  { "shared", "keyword" },
			  { "textureSamples", "keyword" },
			  { "iimageBuffer", "keyword2" },
			  { "iimage1DArray", "keyword2" },
			  { "inversesqrt", "keyword" },
			  { "itexture2DArray", "keyword" },
			  { "barrier", "keyword" },
			  { "textureCubeArray", "keyword" },
			  { "usampler2DMS", "keyword2" },
			  { "atomic_uint", "keyword2" },
			  { "itextureCubeArray", "keyword" },
			  { "fract", "keyword" },
			  { "flat", "keyword" },
			  { "samplerCubeShadow", "keyword2" },
			  { "sampler1DArrayShadow", "keyword2" },
			  { "isampler2DRect", "keyword2" },
			  { "ldexp", "keyword" },
			  { "for", "keyword" },
			  { "normalize", "keyword" },
			  { "buffer", "keyword" },
			  { "sampler1DArray", "keyword2" },
			  { "sampler2DRect", "keyword2" },
			  { "void", "keyword" },
			  { "acosh", "keyword" },
			  { "sign", "keyword" },
			  { "packSnorm4x8", "keyword" },
			  { "case", "keyword" },
			  { "bitfieldInsert", "keyword" },
			  { "isamplerCube", "keyword2" },
			  { "unpackHalf2x16", "keyword" },
			  { "isampler2DArray", "keyword2" },
			  { "uimage2D", "keyword2" },
			  { "unpackSnorm2x16", "keyword" },
			  { "default", "keyword" },
			  { "transpose", "keyword" },
			  { "findMSB", "keyword" },
			  { "coherent", "keyword" },
			  { "exp", "keyword" },
			  { "utexture1D", "keyword" },
			  { "sampler1D", "keyword2" },
			  { "struct", "keyword" },
			  { "uint", "keyword2" },
			  { "NULL", "literal" },
			  { "unpackUnorm2x16", "keyword" },
			  { "break", "keyword" },
			  { "textureQueryLevels", "keyword" },
			  { "sampler2DShadow", "keyword2" },
			  { "sinh", "keyword" },
			  { "isamplerBuffer", "keyword2" },
			  { "sampler2D", "keyword2" },
			  { "iimage2DMSArray", "keyword2" },
			  { "cosh", "keyword" },
			  { "asinh", "keyword" },
			  { "pow", "keyword" },
			  { "floor", "keyword" },
			  { "trunc", "keyword" },
			  { "textureSize", "keyword" },
			  { "round", "keyword" },
			  { "roundEven", "keyword" },
			  { "max", "keyword" },
			  { "ceil", "keyword" },

		  },
		  "//",
		  {}

		} );

	sd.setFoldRangeType( FoldRangeType::Braces ).setFoldBraces( { { '{', '}' } } );
}

}}}} // namespace EE::UI::Doc::Language
