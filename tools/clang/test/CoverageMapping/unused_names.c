// RUN: %clang_cc1 -fprofile-instrument=clang -fcoverage-mapping -emit-llvm -main-file-name unused_names.c -o - %s > %t
// RUN: FileCheck -input-file %t %s
// RUN: FileCheck -check-prefix=SYSHEADER -input-file %t %s

// Since foo is never emitted, there should not be a profile name for it.

// CHECK-DAG: @__profn_bar = {{.*}} [3 x i8] c"bar"
// CHECK-DAG: @__profn_baz = {{.*}} [3 x i8] c"baz"
// CHECK-DAG: @__profn_unused_names.c_qux = {{.*}} [18 x i8] c"unused_names.c:qux"
// CHECK-DAG: @__llvm_prf_nm = private constant {{.*}}, section "{{.*}}__llvm_prf_names"

// SYSHEADER-NOT: @__profn_foo =


#ifdef IS_SYSHEADER

#pragma clang system_header
inline int foo() { return 0; }

#else

#define IS_SYSHEADER
#include __FILE__

int bar() { return 0; }
inline int baz() { return 0; }
static int qux() { return 42; }

#endif
