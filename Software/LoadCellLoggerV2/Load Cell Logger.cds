<distribution version="15.0.0" name="Load Cell Logger" type="MSI64">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{D5D4FB45-A015-4807-93E9-06621EB83BD7}" x64="true">
		<general appName="Load Cell Logger" outputLocation="d:\Documents\CVI\Load Cell Logger V2\cvidistkit.Load Cell Logger" relOutputLocation="cvidistkit.Load Cell Logger" outputLocationWithVars="d:\Documents\CVI\Load Cell Logger V2\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.6">
			<arp company="Guy Yaros" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="Load Cell Logger" subject="" keyWords="" comments="" author="Guy Yaros"/></general>
		<userinterface language="English" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="Load Cell Logger" welcomeText=""/></userinterface>
		<dirs appDirID="100">
			<installDir name="[Program Files]" dirID="24" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Desktop]" dirID="0" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="Load Cell Logger" dirID="100" parentID="24" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="icon" dirID="101" parentID="105" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Guyaros logo" dirID="102" parentID="105" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="DataLogging" dirID="103" parentID="100" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Capture" dirID="104" parentID="100" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="images" dirID="105" parentID="100" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Load Cell Logger" dirID="106" parentID="7" isMSIDir="false" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="d:\Documents\CVI\Load Cell Logger V2\LoadCellLoggerV2.uir" relSourcePath="LoadCellLoggerV2.uir" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="d:\Documents\CVI\Load Cell Logger V2\cvibuild.LoadCellLoggerV2\Release64\LoadCellLoggerV2.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="D:\Documents\CVI\Load Cell Logger V2\images\Guyaros logo\GuyarosLogoCropped10_.png" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="D:\Documents\CVI\Load Cell Logger V2\DataLogging\TempData.csv" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="4" sourcePath="D:\Documents\CVI\Load Cell Logger V2\images\Guyaros logo\GuyarosLogoCropped30_.png" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="5" sourcePath="D:\Documents\CVI\Load Cell Logger V2\Capture\28.05.201716-51-26.jpg" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="6" sourcePath="D:\Documents\CVI\Load Cell Logger V2\images\icon\S-beam256.ico" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="7" sourcePath="D:\Documents\CVI\Load Cell Logger V2\Capture\28.05.201716-54-40.jpg" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput64 targetType="0" dirID="100" projectID="0">
				<fileID>1</fileID></projectOutput64>
			<projectDependencies64 dirID="100" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="Load Cell Logger" targetFileID="1" destDirID="106" cmdLineArgs="" description="" runStyle="NORMAL"/>
			<shortcut name="Load Cell Logger" targetFileID="1" destDirID="0" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine installToAppDir="false" activeXsup="true" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="true">
			<hasSoftDeps/></runtimeEngine><sxsRuntimeEngine>
			<selected>false</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WINXP</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="NI LabWindows/CVI Shared Runtime 2015 SP1" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{48504886-5F3A-4D8B-B8A8-1D755397C43F}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="15.0.1240">
				<dependencies>
					<productID>{04521472-E5D0-49A0-BE27-A2F4805BDE74}</productID>
					<productID>{08505CC2-EA7F-4818-9C45-B74EDA7227F8}</productID>
					<productID>{0C467D7F-52E1-4A92-9481-84BFF097090E}</productID>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{13077484-2D4C-411C-B2A1-DC558FEA45E6}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{21B81C08-8854-4C2D-99E2-6CECA2D468A8}</productID>
					<productID>{22F31177-33F5-4BB5-872D-B43459113AB1}</productID>
					<productID>{2909BF38-1E6A-40C8-88B4-DE370A812B01}</productID>
					<productID>{300AB116-1D42-476D-927A-90391A016DD5}</productID>
					<productID>{327E3A97-A9C7-4C85-B387-E4AB1D27DE74}</productID>
					<productID>{340ADF5D-0206-47CC-9F45-D05E324EF415}</productID>
					<productID>{405BA31C-3A17-47EC-9075-D18B09387C32}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5E207DE6-086F-4548-9052-0DCCD3480C6A}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{72B959AA-19D8-47E5-91C2-ECA967017494}</productID>
					<productID>{7F93F26A-E5F7-4AE1-840F-F88DFE2DE3A5}</productID>
					<productID>{87E698D6-02AC-485E-A6BA-9194C94CC547}</productID>
					<productID>{A64EEEED-6B8D-4369-AEDB-A65ABC3D5C9C}</productID>
					<productID>{B3B56C15-80A8-4972-90CB-D80E64B3F39C}</productID>
					<productID>{C1731602-D122-42AC-8DE5-FB31E7831B93}</productID>
					<productID>{C43C1A6D-71EC-4C88-B489-D53D34716C1D}</productID>
					<productID>{C89B5C4E-B14D-4110-9067-69EB66B4B252}</productID>
					<productID>{CE9BC910-D93D-4083-93C7-0827EDAABC68}</productID>
					<productID>{D0647A03-5158-45FB-844E-A49EC918C411}</productID>
					<productID>{E84997A1-4D6F-4C0B-B60D-F85B360D2666}</productID>
					<productID>{ECB572E6-5CE3-4E9E-B1B3-16A00E02153A}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID></dependencies></product></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="d:\Documents\CVI\Load Cell Logger V2\LoadCellLoggerV2.prj" ProjectRelativePath="LoadCellLoggerV2.prj"/></Projects>
		<buildData progressBarRate="2.922669197094160">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.158398671875036</ProductsAdded>
				<DPConfigured>0.942773312499983</DPConfigured>
				<DPMergeModulesAdded>1.809492546875090</DPMergeModulesAdded>
				<DPClosed>5.251678765625048</DPClosed>
				<DistributionsCopied>5.543229265625043</DistributionsCopied>
				<End>34.215298843750155</End></progressTimes></buildData>
	</msi>
</distribution>
