Pod::Spec.new do |s|

  s.name         = "Pulse_tvOS"
  s.version      = "2.6.23.1.0"
  s.summary      = "High level SDKs to integrate ad serving from Invidi Pulse into your video player application."
  s.description  = "Pulse SDK is the name of a range of SDKs, which simplifies integrating a video player application with Invidi Pulse for ad serving significantly. The Pulse SDKs define a strict and simple communication protocol, allowing developers to quickly build simple event driven integrations."
  s.homepage     = "http://www.invidi.com/"
  s.license      = "MIT"
  s.author       = "Invidi"
  s.platform     = :tvos, "16.0"
  s.source       = { :git => "https://github.com/INVIDITechnologies/pulse-sdk-ios-release", :tag => "#{s.version}" }
  s.vendored_frameworks = "Pulse_tvOS.framework"
  s.requires_arc = true

end
