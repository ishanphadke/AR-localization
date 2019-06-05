# AR-localization
This ROS package aims to autonomously localize a robot using AR markers. After populating the ar_tags_location.txt file with the id and location of each AR tag, a robot using the monte carlo localization method, or amcl, will be able to estimate its position quite accurately in relation to the AR Markers. The robot initially moves in a completely random manner, and upon finding an AR marker, publishes its current position in relation to the AR marker to amcl.
 
