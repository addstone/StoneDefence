# StoneDefence
## [gitee同步仓库](https://gitee.com/smartuil/StoneDefence)

---
* ue版本  4.24.3
* vs版本  2017
* 每一个commit对应一小节
* 欢迎PR

---

Developed with Unreal Engine 4

---
# 第一章：游戏架构
|||
| --------   | -----  |
|第一节：StoneDefence核心架构分析|:heavy_check_mark:|
|第二节：StoneDefence_UI架构分析|:heavy_check_mark:|
|第三节：StoneDefence角色架构分析|:heavy_check_mark:|
|第四节：StoneDefence核心资源和数据架构分析|:heavy_check_mark:|
|第五节：扩展到整个游戏架构设计与分析|:heavy_check_mark:|
---
# 第二章：核心模块搭建
|||
| --------   | -----  |
|第一节：添加屏幕视口|:heavy_check_mark:|
|第二节：封装屏幕移动功能到插件|:heavy_check_mark:|
|第三节：搭建Hall大厅|:heavy_check_mark:|
|第四节：流程关卡|:heavy_check_mark:|
|第五节：游戏标准UI框架搭建|:heavy_check_mark:|
|第六节：布局UMG游戏UI|:heavy_check_mark:|
| 第七节：编写ScreenLoading插件|:heavy_check_mark:|
| 第八节：封装独立UI插件|:heavy_check_mark:|
|第九节：定制Hall大厅UI|:heavy_check_mark:|
|第十节：实现通用的UI切换|:heavy_check_mark:|
---
# 第三章：角色系统搭建
|||
| --------   | -----  |
|第一节：基础角色接口|:heavy_check_mark:|
|第二节：炮塔材质与动画|:heavy_check_mark:|
|第三节：动画状态机|:heavy_check_mark:|
|第四节：编写通用材质|:heavy_check_mark:|
|第五节：拖尾特效制作|:heavy_check_mark:|
|第六节：自定义UE4碰撞通道|:heavy_check_mark:|
|第七节：Cpp怪物AI|:heavy_check_mark:|
|第八节：AI的BTService设计|:heavy_check_mark:|
|第九节：AI_怪物查询敌人算法|:heavy_check_mark:|
|第十节：Towers范围查询敌人算法|:heavy_check_mark:|
---
# 第四章：技能轨迹设计
|||
| --------   | -----  |
|第一节：怪物的AI范围攻击算法|:heavy_check_mark:|
|第二节：子弹类设计|:heavy_check_mark:|
|第三节：发射子弹的AnimNotify_runtime和Editor表现|:heavy_check_mark:|
|第四节：子弹伤害设计|:heavy_check_mark:|
|第五节：子弹碰撞和发射逻辑|:heavy_check_mark:|
|第六节：子弹跟踪设计|:heavy_check_mark:|
|第七节：子弹的范围原理详讲|:heavy_check_mark:|
|第八节：丢手雷数学模型分析|:heavy_check_mark:|
|第九节：雷电持续伤害特效加代码|:heavy_check_mark:|
|第十节：真正商业采用的子弹跟踪方案|:heavy_check_mark:|
|第十一节：花样跟踪的代码实现|:heavy_check_mark:|
---
# 第五章：服务端角色数据搭建
|||
| --------   | -----  |
|第一节：角色数据详细讲解|:heavy_check_mark:|
|第二节：理解UE4中心数据管理|:heavy_check_mark:|
|第三节：数据驱动角色|:heavy_check_mark:|
|第四节：注册角色|:heavy_check_mark:|
|第五节：角色生成与调试|:heavy_check_mark:|
|第六节：更新血条方案|:heavy_check_mark:|
|第七节：伤害公式|:heavy_check_mark:|
|第八节：闪电持续伤害方案|:heavy_check_mark:|
|第九节：游戏数据存档|:heavy_check_mark:|
|第十节：数据列表存储和读取|:heavy_check_mark:|
---
# 第六章：背包数据交互的设计思路
|||
| --------   | -----  |
|第一节：屏幕绘制伤害字体|:heavy_check_mark:|
|第二节：物品栏数据规划|:heavy_check_mark:|
|第三节：物品栏服务的数据和客户端数据|:heavy_check_mark:|
|第四节：数据驱动UI|:heavy_check_mark:|
|第五节：背包信息数据效果显示|:heavy_check_mark:|
|第六节：CD材质函数的数学原理|:heavy_check_mark:|
|第七节：构造塔效果实现|:heavy_check_mark:|
|第八节：实现物品栏进行拖拽功能|:heavy_check_mark:|
|第九节：数据层实现物品交换|:heavy_check_mark:|
---
# 第七章：拖拽与构建塔
|||
| --------   | -----  |
|第一节：显示物品栏塔的介绍代码实现|:heavy_check_mark:|
|第二节：UI映射简介|:heavy_check_mark:|
|第三节：构建功能的按键绑定思路|:heavy_check_mark:|
|第四节：提取特效里面的UStaticMesh|:heavy_check_mark:|
|第五节：通过射线检测实现拖拽生成塔方案|:heavy_check_mark:|
|第六节：实现绿色模型尺寸准确生成|:heavy_check_mark:|
|第七节：RowMesh详细讲解|:heavy_check_mark:|
|第八节：蒙皮网格渲染数据拷贝到静态网格|:heavy_check_mark:|
|第九节：如何修正模型变换位置|:heavy_check_mark:|
---
# 第八章：制作数据与视频插件
|||
| --------   | -----  |
|第一节：如何为模型渲染四边形网格|:heavy_check_mark:|
|第二节：查看角色详细信息功能|:heavy_check_mark:|
|第三节：集火UI效果|:heavy_check_mark:|
|第四节：玩家数据和游戏场景数据|:heavy_check_mark:|
|第五节：游戏Toolbar数据显示|:heavy_check_mark:|
|第六节：编写视频代码|:heavy_check_mark:|
|第七节：视频蓝图修正|:heavy_check_mark:|
|第八节：视频列表|:heavy_check_mark:|
|第九节：视频UI动画代码编写|:heavy_check_mark:|
|第十节：视频倍速与视频声音问题|:heavy_check_mark:|
---
# 第九章：怪物生成器和角色升级系统
|||
| --------   | -----  |
|第一节：怪物的生成方案|:heavy_check_mark:|
|第二节：每波怪物生成的抢红包算法|:heavy_check_mark:|
|第三节：如何设计怪物的出场难度|:heavy_check_mark:|
|第四节：测试怪物生成器|:heavy_check_mark:|
|第五节：角色的升级系统开发|:heavy_check_mark:|
|第六节：升级系统测试|:heavy_check_mark:|
|第七节：角色死亡方案和金币增益方案|:heavy_check_mark:|
|第八节：主塔模型导入和修正|:heavy_check_mark:|
|第九节：主塔特效制作|:heavy_check_mark:|
|第十节：主塔攻击与攻击材质和特效|:heavy_check_mark:|
|第十一节：家庭作业第三个塔的检查|:heavy_check_mark:|