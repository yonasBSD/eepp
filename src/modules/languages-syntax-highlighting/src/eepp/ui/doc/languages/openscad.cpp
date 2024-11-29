#include <eepp/ui/doc/languages/openscad.hpp>
#include <eepp/ui/doc/syntaxdefinitionmanager.hpp>

namespace EE { namespace UI { namespace Doc { namespace Language {

void addOpenSCAD() {

	SyntaxDefinitionManager::instance()->add(

		{ "OpenSCAD",
		  { "%.scad$" },
		  {
			  { { "//.*" }, "comment" },
			  { { "/%*", "%*/" }, "comment" },
			  { { "\"", "\"", "\\" }, "string" },
			  { { "'", "'", "\\" }, "string" },
			  { { "-?0x%x+" }, "number" },
			  { { "-?%d+[%d%.eE]*[a-zA-Z]?" }, "number" },
			  { { "-?%.?%d+" }, "number" },
			  { { "[%+%-=/%*%^%%<>!~|&%?%:]" }, "operator" },
			  { { "[%a_][%w_]*%f[(]" }, "function" },
			  { { "%$%a+" }, "keyword" },
			  { { "[%a_][%w_]*" }, "symbol" },
			  { { "%s+" }, "normal" },
			  { { "%w+%f[%s]" }, "normal" },

		  },
		  {
			  { "str", "function" },
			  { "version", "function" },
			  { "is_undef", "function" },
			  { "ln", "keyword" },
			  { "len", "keyword" },
			  { "rotate_extrude", "keyword" },
			  { "linear_extrude", "keyword" },
			  { "exp", "keyword" },
			  { "render", "keyword" },
			  { "min", "keyword" },
			  { "union", "keyword" },
			  { "search", "function" },
			  { "undef", "keyword2" },
			  { "concat", "function" },
			  { "ord", "function" },
			  { "color", "keyword" },
			  { "norm", "keyword" },
			  { "false", "literal" },
			  { "for", "keyword" },
			  { "is_function", "function" },
			  { "lookup", "function" },
			  { "function", "keyword" },
			  { "difference", "keyword" },
			  { "asin", "keyword" },
			  { "is_list", "function" },
			  { "polyhedron", "keyword" },
			  { "multmatrix", "keyword" },
			  { "chr", "function" },
			  { "is_string", "function" },
			  { "cylinder", "keyword" },
			  { "rotate", "keyword" },
			  { "use", "keyword" },
			  { "sin", "keyword" },
			  { "translate", "keyword" },
			  { "let", "keyword" },
			  { "ceil", "keyword" },
			  { "hull", "keyword" },
			  { "is_bool", "function" },
			  { "version_num", "function" },
			  { "scale", "keyword" },
			  { "atan2", "keyword" },
			  { "intersection", "keyword" },
			  { "each", "keyword" },
			  { "include", "keyword" },
			  { "floor", "keyword" },
			  { "minkowski", "keyword" },
			  { "surface", "keyword" },
			  { "polygon", "keyword" },
			  { "PI", "keyword2" },
			  { "var", "keyword" },
			  { "import", "keyword" },
			  { "max", "keyword" },
			  { "resize", "keyword" },
			  { "pow", "keyword" },
			  { "tan", "keyword" },
			  { "is_num", "function" },
			  { "projection", "keyword" },
			  { "echo", "keyword" },
			  { "circle", "keyword" },
			  { "module", "keyword" },
			  { "sphere", "keyword" },
			  { "assert", "keyword" },
			  { "square", "keyword" },
			  { "rands", "keyword" },
			  { "mirror", "keyword" },
			  { "sign", "keyword" },
			  { "true", "literal" },
			  { "cube", "keyword" },
			  { "text", "keyword" },
			  { "sqrt", "keyword" },
			  { "abs", "keyword" },
			  { "round", "keyword" },
			  { "parent_module", "function" },
			  { "cross", "keyword" },
			  { "acos", "keyword" },
			  { "cos", "keyword" },
			  { "children", "keyword" },
			  { "offset", "keyword" },
			  { "atan", "keyword" },
			  { "log", "keyword" },

		  },
		  "//",
		  {}

		} );
}

}}}} // namespace EE::UI::Doc::Language
