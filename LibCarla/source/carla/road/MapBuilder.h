// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "carla/road/Map.h"
#include "carla/geom/Location.h"

#include <map>

namespace carla {
namespace road {

  class MapBuilder {
  public:

    bool AddRoadSegmentDefinition(RoadSegmentDefinition &seg);

    void SetJunctionInformation(const std::vector<carla::road::lane_junction_t> &junctionInfo)
    {
      _map.SetJunctionInformation(junctionInfo);
    }

    Map Build();

  private:

    template <typename T, typename ... Args>
    T &MakeElement(id_type id, Args && ... args) {
      auto inst = std::make_unique<T>(std::forward<Args>(args) ...);
      T &r = *inst;
      _map._elements.emplace(id, std::move(inst));
      return r;
    }

    bool InterpretRoadFlow();

  private:

    Map _map;
    std::map<id_type, RoadSegmentDefinition> _temp_sections;
  };

} // namespace road
} // namespace carla
