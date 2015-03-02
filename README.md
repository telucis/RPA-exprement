# RPA-exprement
阻滞电位发生器原理性试验


#热层大气风场探测
热层大气是地球近地空间环境的重要组成部分，也是影响日地空间灾害环境和空间天气变化的一个关键环节。
热层大气风场探测目前采用的主要技术手段是采用质谱-阻流挡板设计法
<br>

#工作原理
平行风速测量传感器主要由开源离子源、阻滞电位分析器和离子检测组成，用来测量进入传感器的中性气体动能，
由此推算出沿轨道面中性风分量（即纬向风分量Vx）。
<br>
自然大气中的中性气体分子（原子）、电子、离子一起通过测孔进入传感器，通过离子/电子阱后自然大气中电子、
离子被俘获，而中性气体分子（原子）直接进入离子源电离区，其间经光子抑制区后，可能受太阳光照而射入的光子被屏蔽。
中性气体分子（原子）被电离，所形成离子进入阻滞电位分析区，当阻滞电位栅加上正电位时，就可决定通过阻滞电位栅的离子能量。
改变阻滞电位栅上正电位，以扫描方式形成0～+20V左右的正电位变化时，总量离子收集栅上总量离子流和四极虑质栖
后法拉第筒所收集的谱离子流大小（I）随阻滞电位（V）而变化，来推算沿轨道面的中性气体风速分量。

#设计参数
    风速测量范围：60m/s～1000m/s
    平行风速精度：≤60m/s
    垂直风速精度：≤30m/s
		探测高度：500km---600km
    分压力范围：1×10-8Pa---------1×10-5Pa
    离子流范围：1×10-13 A --1×10-10 A

#实现途径
##阻滞电位
  阻滞电位发生器两秒内产生0V—10V的扫描电压信号，电压加离子源阻滞栅上，阻挡低于阻滞偏压能量的离子进入收集极。<br>
采用双路DA输出电路，第二路RPA输出为阻滞电位发生器的输出信号，连接离子源的阻滞栅。
DA采用AD公司的AD7237芯片，可提供双路12位模拟电压量输出。
##谱信号静电计放大器
  *密度离子流：1х10-13～5х10-11A，采用线性放大器（0.1皮安级微电流放大器）
  *平行风离子流：1х10-13～5х10-11A，采用线性放大器
  *垂直风离子流：1х10-13～5х10-11A，采用线性放大器
  *成分离子流：1х10-13～5х10-11A，采用线性放大器
              1х10-16～1х10-13A，采用MCP和电荷放大器方式
  *总量离子流：1х10-13～5х10-11A，采用对数放大器
  由静电计AD549和高阻组成的线性放大器最小能检测到的电流在1х10-13A以下，温度漂移率在0.3%以下
##离子源和四极杆偏置电源
  离子源和四级杆偏置电源由变流器提供，变流器采用一般的直流变换电路。通过两个3DD153组成的推挽振荡电路起振，
  变压器耦合后经整流、滤波后输出。供给栅极高压180V，供给灯丝电压7.5V，供给四级杆偏置电压为140V左右，四级杆
  偏置电压输出可调节。
  
  附：原理图、PCB与下位机软件
