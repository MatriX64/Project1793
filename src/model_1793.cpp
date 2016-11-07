#include "include/model_1793.h"
#include "include/global_variables_1793.h"

Model_1793::Model_1793()
{

}

Model_1793::Model_1793(Model_1793 *model)
{
    str = "Test";
}

Model_1793::~Model_1793()
{
    emit send_log_file(LogInfoMsg, "Модель уничтожена");
}

void Model_1793::start()
{
    emit send_log_file(LogInfoMsg, "Модель запущена");
    model = this;
}
