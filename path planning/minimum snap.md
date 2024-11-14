# 平滑的一维轨迹
简单的BVP问题（两点边界值问题），已知始末状态，通过参数化来调整平滑度。  
![image](https://github.com/user-attachments/assets/3b706891-ba66-45cb-81fb-5c9713241625)  
使用五次多项式来描述这段轨迹：  
![image](https://github.com/user-attachments/assets/324578fa-7bb7-4d61-acd5-ccbde289d507) 
![image](https://github.com/user-attachments/assets/e1909ff0-cc67-47ee-b251-5fa5a7d73e51)  

# 基于优化的轨迹生成  
Minimum snap问题的限制条件：初始条件以及结束条件的限制（包含有位置，速度，加速度等）；中间节点连续（包含有位置，速度，加速度）  
![image](https://github.com/user-attachments/assets/c66cb94f-59e3-4dce-ba0b-0b472415b02a)  
连续性约束：需要限制中间的航迹点在两段轨迹的接合处是左右两边状态要连续，导数相同  
微分约束：起始点和终点的位置、速度、加速度等使用确定值限制  

Minimum jerk: 最小化角速度，有利于视觉跟踪  
Minimum snap: 最小化差速推力，节省能量  
![image](https://github.com/user-attachments/assets/92cc95fd-09d1-41f8-8a96-3b2a1779d927)  

# 3.Minimum Snap轨迹生成  
![image](https://github.com/user-attachments/assets/eb02998b-a07e-4860-9c2f-990106428116)  
每个段都是一个多项式；每个分段的多项式都是相同的阶次，这样对于问题的求解比较简单； 每一段的时间间隔必须是已知的。  
构建约束方程  
![image](https://github.com/user-attachments/assets/15654d40-8d91-4a0a-b290-737511c5ab4f)  
![image](https://github.com/user-attachments/assets/93129ac4-e4d7-4a13-a505-212d4d6ac78b)  
![image](https://github.com/user-attachments/assets/32036270-2648-44d0-97ab-4abb494bd482)  
![image](https://github.com/user-attachments/assets/e3c6fa34-9ea5-418c-9a69-c1a3e2778b85)  

# 4.闭式求解Minimum Snap  
![image](https://github.com/user-attachments/assets/2e4c2d03-c727-466a-bba1-65dcce572e4c)  





 
