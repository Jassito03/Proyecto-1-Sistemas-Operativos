#include "./disk_t.h"

disk_t disk_t_init(float _total, float _free, float _usage) {
  disk_t disk;
  disk.total = _total;
  disk.free = _free;
  disk.usage = _usage;
  disk.used_percentage = 100.0 * _usage / _total;
  disk.free_percentage = 100.0 * _free / _total;
  return disk;
}