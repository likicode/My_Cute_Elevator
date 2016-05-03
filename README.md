# My_Cute_Elevator
Operating System Project based on OpenFrameWorks

https://github.com/likicode/My_Cute_Elevator/blob/master/ele.png
![Alt text](https://github.com/likicode/My_Cute_Elevator/blob/master/ele.png "A view for the elevator")
### 项目需求
- 基本任务：某一层楼 20 层，有五部互联的电梯。基于线程思想，编写一个电梯调度程序。
- 功能描述：
  - 每个电梯里面应该有一些按键：数字键、关门键、开门键、上行键、下行键、报警键 等。还应该有数码显示器来指示当前电梯的状态。
  - 每层楼的每部电梯门口，应该有上行和下行按钮和当前电梯状态的数码显示器。
  - 五部电梯门口的按钮是互联结的，即当一个电梯按钮按下去时，其他电梯的相应按钮 也就同时点亮，表示也按下去了。
  - 调度算法是根据这五部电梯的状态，寻找离当前楼层 最近的且和请求同方向的电梯给 予响应。
  - 所有电梯初始状态都在第一层。每个电梯如果在它的上层或者下层没有相应请求情况 下，则应该在原地保持不动。
  
###实现平台
- 采用 C++语言编写
- 在 OpenFrameWorks（http://www.openframeworks.cc/ ）环境下开发。它是以 C++为基准 的简洁开发框架，是一个能在多平台上运行的开源项目。

### 项目详细介绍
- 在 OpenFrameWorks 框架下，ofApp.cpp 相当于整个程序的主函数，在其中提供了一些自带 的函数框架：
  - setup()函数负责整个程序开始的初始化。
  - update()函数负责每次自 动刷新程序，除 setup()函数之外，其余函数每次都会在 update()之后执行。
  - draw()函数 负责画出所有图形界面。
  - mousePressed()函数负责相应用户的每一次点击，即负责应答 电梯的楼层请求。
-储存用户请求的容器均用 FIFO 的 queue 来实现。
-我自定义了三个类，每个类负责封装自己负责的模块
  - class Buttons:
  相当于每层楼的电梯外部，位于该层的用户只需选择点击对应的上下按钮来做出请求。
    - draw()：画出程序中的上下按钮。
    - pressed():感应哪个按钮被用户按下，并且将该请求压入 Button:hearReq 里面，并且返回对 应的楼层。
  - class Panel:相当于电梯内部的内置面板，即用户站在电梯内部所看到的界面。
    - draw()/signal():画出面板背景（每层楼的按钮，面板本身，上下显示键）
    - pressed():记录哪部电梯有按键请求，并且返回相应楼层。
  -class Ele:是电梯本身, 并且继承了 OpenFrameWorks 自带 ofThread 类。State 代表电梯的三个状态（running/idle/stop）; direction 代表电梯的方向（-1:向下;1:向上;0:不动）;电梯接受到的任务 全部存放在 ELetask 这个 queue 里面。
    - drawEle():当 state 为 idle 时，只需要在对应位置画出电梯;当 state 为 running 时，需要判断 目标位置方向，并且控制电梯上行的速度（通过 y 坐标变化来控制）;当电梯到达目标为值 时，使线程暂停两秒（sleep(2000)）.
    - 不同运行状态电梯的颜色会发生变化：
    -getFloor():实时判断电梯的当前位置
    - threadedFunction():调用线程自带函数 ofThreadRunning(),如果其值为真，则改变电梯状态 为 idle,如果其值为假，说明进程停止，state 设为 stop
    - Judgement()：当电梯的任务 queue 不为空（if(!Eletask.empty())）并且 queue 内部已经给出 最先相应的楼层时（state == idle && sort）时，把电梯状态改为 running。
    - taskProcess():将分配给该电梯的 button 相应到的目标楼层 push 到 Eletask 里面，并且对现 在已经有任务排序，把离电梯当前楼层最近的任务放在 Eletask.front()的位置，距离最远的最 后处理,因为系统每个时刻都在监测电梯位置，所以距离应按与电梯当前位置最近来算。
  - ofApp
    - setup(): 初始 化五个 电梯（ theEle.push_back(new  Ele()) ，并 且使线 程开始 执行
    - update():每次通过调用 Ele 里面的 Judgement()函数判断电梯是否有任务执行并改变其状 态
    - draw():调用各类里面的 draw()函数。
    - mousePressed():执行 Button 和 Panel 类内部的 Pressed 函数，将 panel 得到的任务直接调用taskProcess 处理，而 Button 得到的任务需要通过 shortest()函数决定具体分配到哪一部电梯。
    - shortest():首先从 Button 类的 queue 里得到最先给出的任务楼层，然后按其方向分类，以 向上为例：找到在其楼层之下并且向上的电梯/在其楼层之上向下的电梯/处于 idle 状态的电 梯，判断哪一个与其距离最小，找到后即为最终响应此任务的电梯。如果是上述情况之外的 情况，就任意分配一部电梯。

###调度策略
在电梯调度中我用了多线程的原则，加上最短调度的策略进行操作。每次选取与目标楼层距 离最近的电梯分配任务，而其余电梯不再响应该任务。



