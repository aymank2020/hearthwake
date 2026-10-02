# مراجعة وتأسيس Hearthwake

قبل العمل: أربعة ملفات Markdown فقط، README/GDD/STATUS/assets. لا uproject ولا Source ولا اختبارات أو build. وعود README تقنية مستقبلية، وحالة pre-production صحيحة.

خطة المرحلة الأولى المنفذة: تأسيس C++17 قابل للبناء، inventory سلطوية محلية وحدود سعة والتحقق من الطلب وتذكر نجاح وفشل ID لمنع إعادة التطبيق وكشف reuse مختلف وحد ذاكرة للطلبات؛ demo حقيقي يستخدم نفس core؛ ثلاثة بوابات CTest للسلوك ومسار CLI ورفض الخيارات؛ CI portable؛ تسجيل مشروع Unreal ووحدة runtime وtargets تستهلك core وتكتب startup log. هذا ليس تنفيذًا لكامل MVP.

البحث: [Epic modules](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-modules)، [Automation Test Framework](https://dev.epicgames.com/documentation/en-us/unreal-engine/automation-test-framework-in-unreal-engine)، [CMake testing](https://cmake.org/cmake/help/latest/command/add_test.html). مصدر القرار الأساسي GDD الحالي: قواعد منفصلة عن العرض وإمكانية إعادة الحالة. يجب تنفيذ اختبار Unreal الحقيقي عند اكتمال المحرك.

التحقق: CMake مع MSVC19.51 وVisual Studio2026 وWindows SDK10.0.26100 بنى Release بنجاح مع /W4 /WX؛ `ctest --test-dir build -C Release --output-on-failure` نجح3/3؛ demo خرج: `wood=4 total=4 retry=deduplicated`. الاختبارات لا تستخدم assert الذي يختفي في Release. `git diff --check` نجح. توقيت الأداء والشبكة غير مقاسين.

التكامل المثبت: CMake -> core-demo CLI -> Core/HearthwakeCore.h -> نتائج الحالة المعروضة أعلاه، ومسار الفشل خروج2. التسجيل المقصود لـUnreal: uproject -> target/Build.cs -> StartupModule -> core -> log. المسار الأخير غير مختبر لأن دليل UE_5.8 لا يحوي Engine/Binaries بل egstore فقط؛ لا claim لبناء Editor أو لعبة. لا بقايا قديمة استُبدلت.

المتبقي: لا شبكة أو RPC أو FastArray أو عميل Unreal أو save/load؛ عند امتلاء تاريخ الطلبات يُرفض الجديد حتى جلسة جديدة، ولا claim لاختبار packet loss. المحرك يجب اكتماله قبل اعتماد M0 بالكامل أو إنتاج packaged build. تبقى مراحل GDD طويلة المدى مفتوحة، فلا تعني foundation اكتمال اللعبة.
