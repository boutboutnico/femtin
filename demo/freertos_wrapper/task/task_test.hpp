/*
 * tsk_test.H
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#ifndef TSK_TEST_H_
#define TSK_TEST_H_

/// === Includes ===================================================================================

#include "freertos_wrapper/task/task.hpp"

/// === Namespaces =================================================================================

namespace femtin
{
namespace demo
{

/// === Class Declarations =========================================================================

class Task1 : public femtin::os::Task
{
public:
  /// --- Public Constants

  static const uint16_t STACK_SIZE        = configMINIMAL_STACK_SIZE;
  static const UBaseType_t STACK_PRIORITY = (tskIDLE_PRIORITY + 2);

  /// --- Public Declarations

  Task1();

  virtual void run();

private:
};

/// === Class Declarations =========================================================================

class Task2 : public femtin::os::Task
{
public:
  /// --- Public Declarations

  Task2() : Task("TSK_T2", configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 1) {}
  virtual void run();
};
/// ------------------------------------------------------------------------------------------------
}
}

#endif
/// === END OF FILE ================================================================================
