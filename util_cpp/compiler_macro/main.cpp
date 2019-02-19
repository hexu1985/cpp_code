#include <iostream>

#if defined(__clang__)
	/* Clang/LLVM. ---------------------------------------------- */
	const char *compiler_name = "Clang/LLVM";

#elif defined(__ICC) || defined(__INTEL_COMPILER)
	/* Intel ICC/ICPC. ------------------------------------------ */
	const char *compiler_name = "Intel ICC/ICPC";

#elif defined(__GNUC__) || defined(__GNUG__)
	/* GNU GCC/G++. --------------------------------------------- */
	const char *compiler_name = "GNU GCC/G++";

#elif defined(__HP_cc) || defined(__HP_aCC)
	/* Hewlett-Packard C/aC++. ---------------------------------- */
	const char *compiler_name = "Hewlett-Packard C/aC++";

#elif defined(__IBMC__) || defined(__IBMCPP__)
	/* IBM XL C/C++. -------------------------------------------- */
	const char *compiler_name = "IBM XL C/C++";

#elif defined(_MSC_VER)
	/* Microsoft Visual Studio. --------------------------------- */
	const char *compiler_name = "Microsoft Visual Studio";

#elif defined(__PGI)
	/* Portland Group PGCC/PGCPP. ------------------------------- */
	const char *compiler_name = "Portland Group PGCC/PGCPP";

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
	/* Oracle Solaris Studio. ----------------------------------- */
	const char *compiler_name = "Oracle Solaris Studio";

#else
	/* Unknown Compiler. ----------------------------------- */
	const char *compiler_name = "Unknown Compiler";

#endif

int main()
{
    std::cout << "this program is compiled by " << compiler_name << std::endl;
	return 0;
}
