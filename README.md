# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## Goal
The purpose of this project was to "build a PID controller and tune the PID hyperparameters by applying the general processing flow as described in the lessons," and to "test your solution on the simulator!" The simulator provides cross-track error (CTE), speed, and steering angle data via local websocket. The PID (proportional/integral/differential) controller must respond with steering and throttle commands to drive the car reliably around the simulator track. 

## Rubric Discussion Points 

### Describe the effect each of the P, I, D components had in your implementation 

PID controllers are a rather basic, but commonly used, class of controllers. PID stands for Proportional, Integral and Derivative Terms. The PID-Controller can be further subdivided into the P-Controller, I-Controller and D-Controller, which can be used separately or as a group to achieve the specific goals depending on the target system. 

The P-Controller outputs a correction based uniquely on the amplitude/strength of the input signal. In our case we feed the P-Controller with the Cross Track Error (or the difference between current speed and reference speed). The larger the input signal the more aggresively the P-Controller tries to compensate. The main problem of the P-Controller is that it tends to overshoot (see image below). Combining the P-Controller with the D-Controller can help solve the overshooting problem. 

The D-Controller reacts to fast changing input signals. The higher the derivative of the input signal the higher the output of the D-Controller. In the figure below we can see that the PD-Controller overcomes the overshooting problem. 
The I-Controller outputs the integral of the error. This is useful to take systemic bias into account (e.g. desalignment of the tyres). In the figure below the PDController shows the best result, since there is no systemic bias in the system, but when systemic bias is present, which is often the case in non-ideal systems, the PID-Controller is the best option. 
![](<https://github.com/Felix-yuan2018/CarND-PID-Control-Project/blob/master/pid.png>)

### Tuning of parameters 

Hyperparameters were chosen manually and iteratively after trial and error driving autonomously around the track. I started with the recommended parameters presented along Sebastian Thrun's PID class: 
- Kp = 0.188 
- Ki = 0.001 
- Kd = 3.147 

Then I tuned parameters, finally got the initial parameters: Kp=0.188, Kd=1.5 and Ki=0.0002. which worked fairly well, and then improved upon that, following is the process: 

The PID controller was implemented in PID.cpp. The method initinitializes the PID with the parameters passed as argument, while in the method UpdateError I use twiddle algorithm to keeps track of the proportional, differential and integral errors of the PID controller. Finally the method TotalError() returns the control input as a result (combining P, I and D corrections). 

The main program main.cpp handles the communication via uWebSockets to the simulator. From lines 35 to 42 two instances of the PID class (one for steering and one for throttle/braking) are created and initialized with the chosen parameters. From lines 63 to 70 both PID controllers are fed every time there is new information coming from the simulator. We pass the Cross Track Error to the PID controlling the steering, which is used to update/compute de PID error and return the steering value. The same is done with the PID controlling the throttle, but in this case we give the difference of the current speed of the car and the reference speed (which is set to 40mph in our case). 

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

