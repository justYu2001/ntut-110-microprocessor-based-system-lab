#ifndef GPIO_H
#define GPIO_H

using namespace std;

void setExport(unsigned int);
void setUnexport(unsigned int);
void setDirection(unsigned int, string);
void setValue(unsigned int, int);

#endif // GPIO_H
