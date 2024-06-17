#include <TwoWayMapManager.h>

template <typename K, typename V>
class CallStarStore : public TwoWayMapManager<K, V> {
 public:
  void insert(K key, V value) override;
};