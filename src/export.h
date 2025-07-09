#ifndef EXPORT_H
#define EXPORT_H 

#include "scanner.h"

void save_as_json(Warning* warnings, int count);
void save_as_csv(Warning* warnings, int count);

#endif