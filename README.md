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
---
# 第十章：如何重构自己的项目
|||
| --------   | -----  |
|第一节：什么是ECS和MVC架构|:heavy_check_mark:|
|第二节：调整我们游戏的整体架构|:heavy_check_mark:|
|第三节：调整游戏数据架构|:heavy_check_mark:|
|第四节：客户端如何调用服务器对象的生成权限|:heavy_check_mark:|
|第五节：技能系统设计和战斗系统设计详讲|:heavy_check_mark:|
|第六节：战斗流程测试场景搭建|:heavy_check_mark:|
|第七节：战斗流程中塔旋转和阵营类型问题|:heavy_check_mark:|
---
# 第十一章：服务器与技能系统架构
|||
| --------   | -----  |
|第一节：技能数据结构设计|:heavy_check_mark:|
|第二节：技能值和属性值的加成思路|:heavy_check_mark:|
|第三节：技能实例增删查改|:heavy_check_mark:|
|第四节：服务器更新技能状态|:heavy_check_mark:|
|第五节：技能系统友军和敌军技能|:heavy_check_mark:|
|第六节：服务器上的群发技能设计|:heavy_check_mark:|
|第七节：子弹类是否应该在服务器生成|:heavy_check_mark:|
|第八节：服务器通知客户端更新技能|:heavy_check_mark:|
|第九节：如何理解WidgetComponent层级问题|:heavy_check_mark:|
|第十节：服务器关联客户端UI技能显示策略|:heavy_check_mark:|
---
# 第十二章：服务器处理玩家技能和被动技能
|||
| --------   | -----  |
|第一节：更新UI角色技能图标|:heavy_check_mark:|
|第二节：解决角色技能系统流程bug|:heavy_check_mark:|
|第三节：通过子弹向中心数据提交数据请求|:heavy_check_mark:|
|第四节：服务器技能生成权限设计思路|:heavy_check_mark:|
|第五节：服务器和客户都技能实例生成流程讲解|:heavy_check_mark:|
|第六节：通过伤害类型CDO建立角色通信约定|:heavy_check_mark:|
|第七节：将服务器计算提交转为客户端角色提交附加技能|:heavy_check_mark:|
|第八节：将物品栏数据的更新移动到服务器|:heavy_check_mark:|
|第九节：玩家技能装备栏制作|:heavy_check_mark:|
|第十节：统一装备栏和玩家技能栏UI逻辑|:heavy_check_mark:|
|第十一节：服务器更新玩家技能思路|:heavy_check_mark:|
|第十二节：玩家核心技能系统搭建|:heavy_check_mark:|
---
# 第十三章：游戏设置
|||
| --------   | -----  |
|第一节：GameSettings图形设计|:heavy_check_mark:|
|第二节：实现各个GameSettings接口调用|:heavy_check_mark:|
|第三节：GameUserSettings精讲解|:heavy_check_mark:|
|第四节：完成GameSettings图形显示|:heavy_check_mark:|
|第五节：如何将浮点保留后两位和后一位|:heavy_check_mark:|
|第六节：游戏设置的读取和保存|:heavy_check_mark:|
|第七节：GameSettings自定义设置键位|:heavy_check_mark:|
|第八节：实现本地化多国语言策略|:heavy_check_mark:|
|第九节：实现音频设置策略|:heavy_check_mark:|
|第十节：实现背景音乐和UI音乐功能设置|:heavy_check_mark:|
|第十一节：背景音乐和UI音乐和游戏音乐设置策略|:heavy_check_mark:|
|第十二节：插件自动化匹配我们的GameUserSettings|:heavy_check_mark:|
---
# 第十四章：游戏的数据存储设计
|||
| --------   | -----  |
|第一节：游戏存储自动注册功能接口|:heavy_check_mark:|
|第二节：游戏存储实例创建思路|:heavy_check_mark:|
|第三节：游戏存储的反向代理|:heavy_check_mark:|
|第四节：设计游戏的存储结构|:heavy_check_mark:|
|第五节：游戏存储后的客户端显示效果|:heavy_check_mark:|
|第六节：客户端发送请求到服务端打开地图|:heavy_check_mark:|
|第七节：如何做游戏数据还原功能|:heavy_check_mark:|
|第八节：统一GameIntance调用接口|:heavy_check_mark:|
|第九节：测试游戏数据存储和还原|:heavy_check_mark:|
|第十节：游戏存储流程测试|:heavy_check_mark:|
|第十一节：解决流程测试中的BUG|:heavy_check_mark:|
---
# 第十五章：游戏弹窗插件和游戏存档
|||
| --------   | -----  |
|第一节：游戏缩略图智能读取|:heavy_check_mark:|
|第二节：游戏缩略图智能生成|:heavy_check_mark:|
|第三节：编写弹窗插件|:heavy_check_mark:|
|第四节：让弹窗自动生成控件button|:heavy_check_mark:|
|第五节：弹窗的样式设定|:heavy_check_mark:|
|第六节：如何正确的在两个插件之间解耦通信|:heavy_check_mark:|
|第七节：对存档进行正确的删除操作|:heavy_check_mark:|
|第八节：将角色数据的地址操作转为指针|:heavy_check_mark:|
|第九节：模型的缓存池设计|:heavy_check_mark:|
|第十节：ToolBar波段数代理|:heavy_check_mark:|
|第十一节：解决游戏中存在的BUG|:heavy_check_mark:|
---
# 第十六章：小地图实现策略
|||
| --------   | -----  |
|第一节：通过场景动态捕捉小地图|:heavy_check_mark:|
|第二节：捕获地形贴图的数学原理|:heavy_check_mark:|
|第三节：旧版本HUD绘制地图数学原理|:heavy_check_mark:|
|第四节：将动态的地图截屏应用到小地图|:heavy_check_mark:|
|第五节：地图移动原理和全局管理策略|:heavy_check_mark:|
|第六节：全局管理架构设计布局思路|:heavy_check_mark:|
|第七节：地图移动和缩放|:heavy_check_mark:|
|第八节：在地图上定位敌人|:heavy_check_mark:|
|第九节：自定义真实感地图切换策略|:heavy_check_mark:|