// Effective-Modern-CPP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

// 类型推导
#include "type_deduction/TemplateTypeDeduction.h"
#include "type_deduction/AutoTypeDeduction.h"
#include "type_deduction/DecltypeUsage.h"

// 现代特性
#include "modern_features/PreferAuto.h"
#include "modern_features/BraceInitialization.h"
#include "modern_features/PreferNullptr.h"
#include "modern_features/ScopedEnums.h"
#include "modern_features/NoexceptFunctions.h"
#include "modern_features/ConstexprUsage.h"
#include "modern_features/ThreadSafeConst.h"
#include "modern_features/SpecialMemberFunctions.h"

// 智能指针
#include "smart_pointers/UniquePtrUsage.h"
#include "smart_pointers/SharedPtrUsage.h"
#include "smart_pointers/WeakPtrUsage.h"
#include "smart_pointers/MakeSmartPtr.h"
#include "smart_pointers/PimplIdiom.h"

// 完美转发
#include "forwarding/PerfectForwarding.h"
#include "forwarding/UniversalReferences.h"
#include "forwarding/OverloadingAlternatives.h"

// Lambda表达式
#include "lambdas/LambdaCaptures.h"
#include "lambdas/InitCapture.h"
#include "lambdas/DecltypeForwarding.h"
#include "lambdas/LambdaVsBind.h"

// 并发编程
#include "concurrency/TaskBasedProgramming.h"
#include "concurrency/ThreadRAII.h"
#include "concurrency/ThreadHandleDestruction.h"
#include "concurrency/EventNotification.h"
#include "concurrency/AtomicVsVolatile.h"
#include "concurrency/PassByValue.h"
#include "concurrency/Emplacement.h"

int main()
{
    Emplacement::Demo().run();
    //EventNotification::DemoPromise().run();
}