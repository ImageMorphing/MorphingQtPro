#ifndef CATMULLROM_H
#define CATMULLROM_H

#include <iostream>
#include <cassert>

#include <QMessageBox>

#include "image_meshwarp.h"

void catmullRom(float *x1, float *y1, int len1, float *x2, float *y2, int len2);

#endif // CATMULLROM_H
