# GAS_net

基于 **Unreal Engine 5.4** 的 Gameplay Ability System(GAS)网络复制示例项目,演示了属性集(Attribute Set)的网络同步、属性变更广播,以及技能信息(冷却 / 消耗 / 图标)的定义与获取。

## 环境要求

| 项目 | 版本 |
| ---- | ---- |
| Unreal Engine | 5.4 |
| Visual Studio | 2022(编译 C++ 代码) |
| Git LFS | 必需(uasset / umap 等资源文件通过 LFS 管理) |

## 功能特性

- **属性集 `UBaseAttributeSet`**:HP、MP、Strength(体力)、Attack、Aromo 等属性,全部通过 `DOREPLIFETIME_CONDITION_NOTIFY` 进行网络复制,并在 `PostGameplayEffectExecute` 中对 HP / MP / Strength 做范围钳制(Clamp 到 `[0, Max]`)。
- **属性变更事件**:角色在 `BeginPlay` 时向 AbilitySystemComponent 注册属性变更委托,对外广播 `HealthChangedEvent` / `MPChangedEvent` / `StrengthChangedEvent`,供 UI 等模块监听。
- **技能信息 `FGameplayAbilityInfo`**:每个技能可配置冷却时间(CD)、消耗类型(HP / MP / Strength)与消耗值、图标材质,通过 `GetAbilityInfo()` 查询。
- **蓝图可扩展**:所有基础类均暴露 `BlueprintReadWrite` / `BlueprintCallable` / `BlueprintAssignable`,便于在蓝图中派生与使用。

## 项目结构

```
GAS_net/
├── GAS_net.uproject          # 项目描述文件(已启用 GameplayAbilities 插件)
├── Config/                   # 项目配置(引擎、游戏、输入、GameplayTags 等)
├── Content/
│   ├── Ani/                  # 动画蓝图与蒙太奇(Death / Melee / Regen)
│   ├── Assets/               # 技能资源、特效、UI 素材
│   ├── BP/                   # 蓝图
│   ├── Characters/           # 角色
│   ├── Map/                  # 关卡地图
│   ├── ParagonShinbi/        # Paragon Shinbi 角色资源
│   └── ...
└── Source/
    └── GAS_net/
        ├── Public/
        │   ├── BaseAttributeSet.h      # 属性集:HP/MP/Strength/Attack/Aromo
        │   ├── BaseCharacter.h         # 角色基类:属性变更事件广播
        │   └── BaseGameplayAbility.h   # 技能基类:技能信息(CD/消耗/图标)
        └── Private/                    # 对应实现文件
```

## 核心类说明

### UBaseAttributeSet

继承自 `UAttributeSet`,包含以下属性(全部网络复制 + `REPNOTIFY_Always`):

| 属性 | 说明 |
| ---- | ---- |
| HP / MaxHP | 生命值及其上限 |
| MP / MaxMP | 法力值及其上限 |
| Strength / MaxStrength | 体力值及其上限 |
| Attack | 攻击力 |
| Aromo | 护甲 |

- `PostGameplayEffectExecute`:Gameplay Effect 结算后钳制 HP / MP / Strength 到合法范围。
- `OnHPChanged`:HP 变化时广播 `NewHP` 与 `MaxHP`(供血条 UI 使用)。

### ABaseCharacter

继承自 `ACharacter`:

- 在 `BeginPlay` 中获取 `UAbilitySystemComponent`,注册 HP / MP / Strength 属性变更委托;
- 通过 `HealthChangedEvent` / `MPChangedEvent` / `StrengthChangedEvent` 向蓝图或 UI 广播属性变化;
- `GameplayAbilityInfo(AbilityClass, Level)`:查询指定技能的 `FGameplayAbilityInfo`。

### UBaseGameplayAbility

继承自 `UGameplayAbility`:

- 每个技能携带 `IconMaterial` 图标材质;
- `GetAbilityInfo(Level)` 返回技能信息结构体 `FGameplayAbilityInfo`,包含:
  - `CD`:冷却时间
  - `CostType`:消耗类型(`ECostType::HP / MP / Strength`)
  - `CostValue`:消耗数值
  - `IconMaterial`:技能图标材质

## 构建与运行

1. 确保已安装 **UE 5.4**、**Visual Studio 2022** 和 **Git LFS**;
2. 克隆仓库(资源文件由 Git LFS 管理):
   ```bash
   git lfs install
   git clone <仓库地址>
   ```
3. 双击 `GAS_net.uproject` 打开项目,或右键选择 **Generate Visual Studio project files** 后用 Visual Studio 编译;
4. 在编辑器中打开 `Content/Map` 下的地图并点击 **Play**。

## 网络测试

- 编辑器主窗口菜单:**Play → Number of Players → 2(或以上)**,即可在 Listen Server 模式下观察属性网络复制效果。

## 版本控制说明

- 大文件(uasset / umap / fbx / 贴图 / 音频)通过 **Git LFS** 管理,提交或克隆前请先执行 `git lfs install`;
- `Binaries` / `Intermediate` / `Saved` 等编译产物已加入 `.gitignore`。

## 参考资源

- [Gameplay Ability System 官方文档](https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine)
- [GASDocumentation (tranek)](https://github.com/tranek/GASDocumentation)
