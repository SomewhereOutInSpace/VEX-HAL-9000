#pragma once
#include "robokauz/PRELUDE.hpp"
#include "robokauz/COMMON.hpp"
#include "robokauz/PURE_PURSUIT.hpp"
#include "robokauz/Autonomous/IMUOdometry.hpp"

enum GenerationMode
{
    Spline,
    ConstrainedSpline,
    Rough
};

class PathBuilder
{
    private:

        std::string path_name;

        GenerationParameters gen_params;

        RobotProperties robot_props;

        std::vector<Waypoint> path_waypoints;

        PathManager& calling_manager;

        int generation_mode = Spline;

        bool has_prealignment = false;

        bool compute_reversed = false;

        bool do_debug_dump = false;

        const QLength injection_spacing = 1.5_in;

        std::vector<squiggles::Pose> transformToCartesian();

        std::vector<squiggles::ProfilePoint> generateConstrainedSplinePath(std::vector<squiggles::Pose> waypoints);

        std::vector<PathPoint> stripConstrainedSplineForExport(std::vector<squiggles::ProfilePoint> path);

        std::vector<PathPoint> injectPoints();

        void calculateCurvatures(Path& path);

        void calculateVelocities(Path& path);

        Path calculatePath();

    public:

        PathBuilder(std::string name, GenerationParameters g_params, RobotProperties r_props, PathManager& caller);

        PathBuilder withRobotProperties(RobotProperties r_props);

        PathBuilder withGenerationMode(int mode);

        PathBuilder withPoint(Waypoint point);

        PathBuilder withPoints(std::vector<Waypoint> points);

        PathBuilder withOrigin();

        PathBuilder withRotatedOrigin(QAngle rotation);

        PathBuilder withCurrentPosition(IMUOdometer& odometer);

        PathBuilder withPrealignment();

        PathBuilder makeReversed();

        PathBuilder withDebugDump();

        void generatePath();
};
